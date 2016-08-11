/*
 * The ftp server, with the quick big file transferring, control options and so on.
 * Base on Linux epoll + boost::thread/mutex .
 * Every 1000 parallel connections need less than 10M memory.
 * If you did a memory pool just like the boost, it would be more effective.
 * The client code could be rewrite.
 * 
 * PS:
 * Keep on working this, more robust and available.
 */
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>                /* FILE STAT STRUCT */
#include <netinet/in.h>              /* SOCKET STRUCT */
#include <arpa/inet.h>               /* NETWORK FUNCTIONS */
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <ctime>
#include <vector>
#include <queue>
#include <tr1/unordered_map>
#include <algorithm>
using namespace std;

#include "mysql_driver.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/statement.h"
#include "cppconn/resultset.h"
using namespace sql;

#include "ftp_class.h"
#include "ftp_func.h"

extern string get_user_name();
extern string get_password();

/* Thread Pool */
thread_pool my_thread_pool(FTP_MAX_QUEUE);
mysql::MySQL_Driver* driver = mysql::get_driver_instance();
Connection* con;

/* According to the type, get the client. */
static inline FTPClient& type_of(vector<FTPClient>& clients,
        tr1::unordered_map<int, int>& d_c,
        tr1::unordered_map<int, int>& socks,
        const int& sockfd,
        const int& type)
{
    if (type == FTP_CONTROL_TYPE)
        return clients[socks[sockfd]];
    return clients[socks[d_c[sockfd]]];
}

/* According to the type, release and reset the resource. */
static void release_reset(FTPClient& client,
        queue<int>& av_q,
        tr1::unordered_map<int, int>& d_c,
        tr1::unordered_map<int, int>& socks,
        const int& sockfd,
        const int& type)
{
    close(sockfd);
    if (type == FTP_CONTROL_TYPE) {
        demap_socks(socks, sockfd);
        enqueue_client(av_q, client.get_id());
        client.reset();
    }
    else {
        dequeue_data_con(d_c, client.get_data_fd());
    }
}

/* Catch the signal to exit the server, CTRL+C or Kill */
static void exit_confirm(int signal) throw()
{
    string cfm;
    cout << endl;
    cout << "Are you sure to shut down the server?[Y/N]" << endl;
    cin >> cfm;
    transform(cfm.begin(), cfm.end(), cfm.begin(), ::toupper);
    if (cfm == "Y" || cfm == "YES")
        exit(0);
}

/*=====The Most Important Function:Start the ftp server.=====*/
void ftp_server_start()
{
    /* Global db connection. */
    con = driver->connect(DB_PATH, get_user_name(), get_password());
    if (con)
        cout << "Connect to the database successfully!" << endl;
    else {
        cout << "Invalid input, please try again!" << endl;
        exit(0);
    }

    /* The Data Structure. */
    vector<FTPClient> clients(FTP_MAX_QUEUE);
    std::queue<int> available_queue;
    /* MEMORY POOL IN FUTURE */

    /* Handle the signals */
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
	/* TODO -- A Small Bug 
	 * Boost always catches the signal as an assertion and return false.
	 */
    signal(SIGINT, &exit_confirm);
	signal(SIGKILL, &exit_confirm);
	signal(SIGHUP, &exit_confirm);

    /* Server variables */
    int listenfd, datafd, connfd, sockfd, epfd;
    int nfds;
    struct epoll_event ev_cntl, ev_data, events[3 * FTP_MAX_QUEUE / 2];
    struct sockaddr_in server_cntl_addr, server_data_addr;
    struct sockaddr_in client_addr;
    socklen_t c_len;
    char cmd[CMD_MAX_LENGTH];

    /* For client statistics in the future. */
    /* Mapping the socks with the clients.*/
    tr1::unordered_map<int, int> socks;
    tr1::unordered_map<int, int> data_cntl;

    /* Start from here. */
    for (int i = 0; i < FTP_MAX_QUEUE; i++)
        available_queue.push(i);
    epfd = epoll_create(FTP_MAX_QUEUE);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    datafd = socket(AF_INET, SOCK_STREAM, 0);
    set_no_blocking(listenfd);
    set_no_blocking(datafd);

    /* Add the listenfd and data fd to the epoll set. */
    ev_cntl.data.fd = listenfd;
    ev_cntl.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev_cntl);
    ev_data.data.fd = datafd;
    ev_data.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, datafd, &ev_data);

    server_cntl_addr.sin_family = AF_INET;
    // inet_aton("49.140.62.120", &server_cntl_addr.sin_addr); -- real use
    server_cntl_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_cntl_addr.sin_port = FTP_CONTROL_PORT;
    server_data_addr.sin_family = AF_INET;
    //inet_aton("49.140.62.120", &server_data_addr.sin_addr);
    server_data_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_data_addr.sin_port = FTP_DATA_PORT;

    /* Bind the listenfd and the datafd. */
    if (bind(listenfd, (struct sockaddr*) &server_cntl_addr,
            sizeof(server_cntl_addr)) < 0) {
        cout << FTP_LOG_HEAD << " Binding control port error!" << endl;
    }
    listen(listenfd, FTP_MAX_QUEUE);
    if (bind(datafd, (struct sockaddr*) &server_data_addr,
            sizeof(server_data_addr)) < 0) {
        cout << FTP_LOG_HEAD << " Binding data port error!" << endl;
    }
    listen(datafd, FTP_MAX_QUEUE);

    /* Server has been started. */
    time_t t;
    time(&t);
    cout << "=================================" << endl;
    cout << " Time: " << ctime(&t);
    cout << "=================================" << endl;
    cout << FTP_LOG_HEAD << " FTP Server has been started!" << endl;

    /* Default mode is standard. */
    while (1) {
        int i;
        nfds = epoll_wait(epfd, events, FTP_MAX_QUEUE, 2000);
        //cout << "Events:" << nfds << endl;
        for (i = 0; i < nfds; i++) {
            int type;
            /* Listenfd starts working. */
            if (events[i].data.fd == listenfd) {
                char cfb[128];
                connfd = accept(listenfd, (struct sockaddr*) &client_addr, &c_len);

                /* Get the presentation. */
                const char *cfb_ptr = inet_ntop(AF_INET, &client_addr, cfb, sizeof(cfb));

                /* Allocation is failed. */
                if (connfd < 0) {
                    cout << FTP_LOG_HEAD << " A client control connection failed: " <<
                            cfb_ptr << endl;
                    break;
                }
                set_no_blocking(connfd);
                cout << FTP_LOG_HEAD << " Get a client control connection: " << cfb_ptr
                        << ", at: " << connfd << endl;
                clients[connfd].set_id(connfd);
                /* Add the connfd to the socks set. */
                int alloc_id = get_next_client(available_queue);
                socks[connfd] = alloc_id;
                clients[alloc_id].set_id(alloc_id);
                ev_cntl.data.fd = connfd;
                ev_cntl.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev_cntl);
#ifdef DEBUG
                cout << "Add it completely!" << endl;
#endif
            }
            else if (events[i].data.fd == datafd) {
                connfd = accept(datafd, (struct sockaddr*) &client_addr, &c_len);
                if (connfd < 0) {
                    cout << FTP_LOG_HEAD << " A client data connection failed: " <<
                            inet_ntoa(client_addr.sin_addr) << endl;
                    break;
                }
                set_no_blocking(connfd);
                cout << FTP_LOG_HEAD << " Get a client data connection: " << inet_ntoa(client_addr.sin_addr) <<
                        ":" << ntohs(client_addr.sin_port) << ", at: " << connfd << endl;
                /* Can speed up here in future. */
                ev_data.data.fd = connfd;
                ev_data.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev_data);
            } /* Read events */
            else if (events[i].events & EPOLLIN) {
                //cout << "Catch a read event:" << sockfd << endl;
                if ((sockfd = events[i].data.fd) < 0) continue;

                type = judge_sock_type(socks, sockfd);
                FTPClient& client = type_of(clients, data_cntl, socks, sockfd, type);

                while (1) {
                    int recvNum;
                    if (type == FTP_CONTROL_TYPE) {
                        recvNum = read(sockfd, cmd, CMD_MAX_LENGTH);
                        //cout << "Recv:" << recvNum << endl;
                    }
                    else if (type == FTP_DATA_TYPE) {
                        /* TODO -- contact with the client for the data_fd. */
                        recvNum = read(sockfd, client.get_buffer(), FILE_MAX_BUFFER);
                    }
                    if (recvNum < 0) {
                        /* FULL */
                        if (errno == EAGAIN) break;
                        else if (errno == ECONNRESET) {
                            cout << FTP_LOG_HEAD << " " << sockfd << " get a RESET!" << endl;

                            release_reset(client, available_queue, data_cntl, socks, sockfd, type);

                            break;
                        }
                        else if (errno == EINTR) continue;
                        else {
                            cout << FTP_LOG_HEAD << " " << sockfd << " is unrecoverable!" << endl;

                            release_reset(client, available_queue, data_cntl, socks, sockfd, type);

                            break;
                        }
                    }
                    else if (recvNum == 0) {
                        cout << FTP_LOG_HEAD << " " << sockfd << " shuts down normally!" << endl;

                        release_reset(client, available_queue, data_cntl, socks, sockfd, type);
                    }
                    if (type == FTP_CONTROL_TYPE && recvNum <= CMD_MAX_LENGTH) {
                        strncpy(client.last_c_feedback,
                                (process_request(cmd, client, type)).c_str(),
                                FB_MAX_LENGTH);

                        //cout << "GET A FEEDBACK:" << feedback << endl;
                        break;
                    }
                    else if (type == FTP_DATA_TYPE && recvNum <= FILE_MAX_BUFFER) {
                        /* TODO--Read and map the client with the data fd. */
                        string ret = process_request(client.get_buffer(), client, type);
                        if (ret[0] == FTP_RSP_FT_END)
                            dequeue_data_con(data_cntl, sockfd);
                            /* Occur an error, so just return and close. */
                        else if (ret[0] == FTP_RSP_ERR) {
                            write(sockfd, ret.c_str(), ret.size());
                            close(sockfd);
                        }

                        break;
                    }
                    else {
                        release_reset(client, available_queue, data_cntl, socks, sockfd, type);

                        break;
                    }
                }
                if (type == FTP_CONTROL_TYPE) {
                    ev_cntl.data.fd = sockfd;
                    ev_cntl.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev_cntl);
#ifdef DEBUG
                    cout << FTP_LOG_HEAD << " " << sockfd << " is ready to write." << endl;
#endif
                }
                else {
                    ev_data.data.fd = sockfd;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, &ev_data);
                }
            } /* Write events */
            else if (events[i].events & EPOLLOUT) {
                sockfd = events[i].data.fd;

                type = judge_sock_type(socks, sockfd);
                FTPClient& client = type_of(clients, data_cntl, socks, sockfd, type);

                if (type == FTP_CONTROL_TYPE) {
                    write(sockfd, client.last_c_feedback, FB_MAX_LENGTH);
                    ev_cntl.data.fd = sockfd;
                    ev_cntl.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev_cntl);
                }
                else {
                    /* 
                     * If the program get here, 
                     * it just get so close to an error.
                     * We do the jobs in the thread pool.
                     */
                }

            }
        }
    }

    my_thread_pool.join_all();
    delete con;
    return;
}

/* Set the socket with the flag O_NONBLOCK */
void set_no_blocking(const int& sock)
{
    int opts;
    opts = fcntl(sock, F_GETFL);
    if (opts < 0) {
        cerr << "Get sock options error!" << endl;
        exit(1);
    }
    opts |= O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0) {
        cerr << "Set sock options error!" << endl;
        exit(1);
    }
}

/* Process the requests from the clients, and return the feedback */
string process_request(char* p_cmd, FTPClient& client, const int& type)
{
    string rt;
    string rcmd; // REAL CMD
    string args;
    if (type == FTP_CONTROL_TYPE) {
#ifdef DEBUG
        cout << FTP_LOG_HEAD << " Get a control cmd: " << p_cmd << ", at " << sock << endl;
#endif
        /* Split the command. */
        int i;
        int len = strlen(p_cmd);
        for (i = 0; i < len; i++) {
            if (p_cmd[i] != ' ' && p_cmd[i] != '\0' && p_cmd[i] != '\n')
                rcmd += p_cmd[i];
            else
                break;
        }
        for (int j = i + 1; j < len; j++) {
            if (p_cmd[j] != '\0' && p_cmd[i] != '\n')
                args += p_cmd[j];
            else
                break;
        }
        if (rcmd == FTP_CMD_USER) {
            /* Request a password */
            rt = FTP_RSP_R_PASS;
            /* Get from the MySQL Database. */
            strncpy(client.user, rcmd.c_str(), USER_INFO_LENGTH);
        }
        else if (rcmd == FTP_CMD_PASS) {
            /* In the future, this can be another work in the thread pool. */
            /* Get the password by the user, then match them. */
            if (strlen(client.user) >= 3) {
                Statement* stmt = con->createStatement();
                /* 
                 * This place should do some checks and encryption to avoid
                 * security problems just like SQL Injection.
                 */
                string sentence = "select password from ";
                sentence += USER_TABLE;
                sentence += " where name = '";
                sentence += client.user;
                sentence += "'";

                ResultSet* res = stmt->executeQuery(sentence);
                if (args == res->getString(1)) {
                    client.is_logged = true;
                    client.set_password(args.c_str());
                    rt = FTP_RSP_P_PASS;
                }
                delete res;
                delete stmt;
            }
            else
                rt = FTP_RSP_E_PASS;
        }
        else if (rcmd == FTP_CMD_LIST) {
            if (client.is_logged) {
                rt = FTP_RSP_LIST;
                DIR* dir;
                struct dirent* ptr;
                dir = opendir(FTP_DIR);
                while ((ptr = readdir(dir)) != NULL) {
                    /* Strcmp will return a true value while dismatching. */
#ifdef __linux
                    /* Skip the useless dir. */
                    if (!strcmp(ptr->d_name, "."))
                        continue;
                    else if (!strcmp(ptr->d_name, ".."))
                        continue;

                    struct stat file_stat;
                    string file_path(FTP_DIR);
                    string temp;

                    file_path += ptr->d_name;
                    stat(file_path.c_str(), &file_stat);
                    rt += ptr->d_type;
                    rt += " ";
                    rt += ptr->d_name;
                    temp += ptr->d_type;
                    temp += " ";
                    temp += ptr->d_name;
                    for (int pos = temp.length(); pos < 40; pos++)
                        rt += " ";
                    rt += "|";
                    for (int pos = 40; pos < 50; pos++)
                        rt += " ";
                    rt += byte2std(file_stat.st_size);
                    rt += "\n";
#endif
                }
                closedir(dir);
            }
            else
                rt = FTP_RSP_R_LOG;
        }
        else if (rcmd == FTP_CMD_PUT) {
            if (client.is_logged) {
                rt = FTP_RSP_RF_START;
                string file_path(FTP_DIR);
                file_path += args;
                if (!client.ftp_open(file_path))
                    rt = FTP_RSP_ERR;
                else
                    strncpy(client.file_name, args.c_str(), MAX_FILE_NAME);
            }
            else
                rt = FTP_RSP_R_LOG;
        }
        else if (rcmd == FTP_CMD_GET) {
            if (client.is_logged) {
                rt = FTP_RSP_SF_START;
                string file_path(FTP_DIR);
                file_path += args;
                if (!client.ftp_open(file_path, false))
                    rt = FTP_RSP_ERR;
                else
                    strncpy(client.file_name, args.c_str(), MAX_FILE_NAME);
            }
            else
                rt = FTP_RSP_R_LOG;
        }
        else if (rcmd == FTP_CMD_QUIT) {
            rt = FTP_RSP_BYE;
        }
        else
            rt = FTP_RSP_ERR;
        return rt;
    }
    else {
        work* w = new work(&client);
        if (my_thread_pool.push_work(w)) {
            rt = FTP_RSP_FT_END;
        }
        else
            rt = FTP_RSP_ERR;

        return rt;
    }
}

/* Judge the sock is for control or data. */
static inline uint8_t judge_sock_type(tr1::unordered_map<int, int>& s, const int& sock)
{
    if (s.find(sock) != s.end())
        return FTP_CONTROL_TYPE;
    return FTP_DATA_TYPE;
}

/* Dequeue the client with the specified sock. */
static inline void demap_socks(tr1::unordered_map<int, int>& socks, const int& sock)
{
    socks.erase(sock);
}

/* Data connection is finished. */
static inline void dequeue_data_con(tr1::unordered_map<int, int>& d_c, const int& sock)
{
    if (d_c.find(sock) != d_c.end())
        d_c.erase(sock);
}

/* Release a client and add it into available queue. */
static inline void enqueue_client(queue<int>& av_q, const int& ava_id)
{
    av_q.push(ava_id);
}

/* Get a client that has not been used. */
static inline int get_next_client(queue<int>& av_q)
{
    if (!av_q.empty()) {
        int ret = av_q.front();
        av_q.pop();
        return ret;
    }
    return -1;
}

/* Change the file size to a human-readable format. */
string byte2std(const int& size)
{
    string result;
    char std[31];
    if (size >= 1024 * 1024) {
        sprintf(std, "%g", (double) (size / 1024 / 1024));
        result = std;
        result += "MB";
    }
    else if (size >= 1024) {
        sprintf(std, "%g", (double) (size / 1024));
        result = std;
        result += "KB";
    }
    else {
        sprintf(std, "%d", size);
        result = std;
        result += "B";
    }
    return result;
}
