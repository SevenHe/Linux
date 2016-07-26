/*
 * TODO--The server sends the list to the client, but it may a big number, so we need to divide them, 
 *     --and send them step by step.
 */
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>                /* FILE STAT STRUCT */
#include <netinet/in.h>              /* SOCKET STRUCT */
#include <arpa/inet.h>               /* NETWORK FUNCTIONS */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <stdio.h>                   /* FOR sprintf */

#include <iostream>
#include <fstream>
#ifndef __STRING__
#include <string>
#endif
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#ifndef __FTPDEF_H
#include "ftpdef.h"
#endif

/* 
 * Put these classes to an another file in the future. 
 * And encrypt the data.
 */
class FTPClient
{
	private:
		int id;
        int data_port;  /* FOR PASV MODE */
        char pswd[20];
	public:
        bool is_logged;
        char last_feedback[FB_MAX_LENGTH];
        char user[10];
        
        /* Constructor */
        FTPClient()
        {
            this->id = -1;
            this->data_port = 0;
            this->is_logged = false;
        }
        
        /* ID GETTER AND SETTER */
		int get_id()
		{
			return this->id;
		}
		void set_id(int id)
		{
			this->id = id;
		}
		
		/* DATA_PORT GETTER AND SETTER */
		int get_data_port()
        {
            return this->data_port;
        }
        void set_data_port(int port)
        {
            this->data_port = port;
        }
        
        /* OTHER NECESSARY FUNCTIONS */
        void set_password(const char* password)
        {
            strcpy(this->pswd, password);
        }
        void reset()
        {
            this->id = -1;
            this->is_logged = false;
            memset(last_feedback, 0, sizeof(last_feedback));
            memset(user, 0, sizeof(user));
            memset(pswd, 0, sizeof(pswd));
        }
};

void exit_confirm(int signal)
{
	string cfm;
	cout << endl;
	cout << "Are you sure to shut down the server?[Y/N]" << endl;
	cin >> cfm;
	transform(cfm.begin(), cfm.end(), cfm.begin(), ::toupper);
	if(cfm == "Y" || cfm == "YES")
		exit(0);
}

string process_request(char*, int, int);

/*
 * There is a problem that would occur here,  FTP_MAX_QUEUE should be the MAX_FILE_DESCRIPTOR.
 * But the last is too big to save them, so the best way is a map, which would be used in the future.
 */
FTPClient clients[FTP_MAX_QUEUE];
ofstream ofs[FTP_MAX_QUEUE];
ifstream ifs[FTP_MAX_QUEUE];
char buffer[FTP_MAX_QUEUE][FILE_MAX_BUFFER];                // CMD(1 Byte) + DATA
char file_name[FTP_MAX_QUEUE][MAX_FILE_NAME];
/* Just for testing */
ofstream ofs_temp;
ifstream ifs_temp;
char file_name_temp[MAX_FILE_NAME];
/* There could be a global server dir string. */

int main()
{
	/* Handle the signals */
	signal(SIGPIPE, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, &exit_confirm);
	
	/* Server variables */
	int listenfd, datafd, connfd, sockfd, epfd;
	int nfds;
	struct epoll_event ev_cntl, ev_data, events[FTP_MAX_QUEUE];
	struct sockaddr_in server_cntl_addr, server_data_addr;
	struct sockaddr_in client_addr;
	socklen_t c_len;
	char cmd[CMD_MAX_LENGTH];
	char feedback[FB_MAX_LENGTH];
	int seq[FTP_MAX_QUEUE];                                    // FOR DATA TRANSFORMATION SEQUENCE
	/* For client */
	vector<int> socks;                                         // CONTROL SOCKETS
	map<int, string> data_feedback;                            // FOR FUTURE ANALYSIS
	// TODO--do the mapping from a control link to a data link, buf for now just use a variable.
	
	/* Initialization */
	memset(seq, -1, sizeof(seq));
	vector<int>::iterator iter;
	map<int, string>::iterator miter;

	/* Start from here. */
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
    server_data_addr.sin_port  = FTP_DATA_PORT;
    
    /* Bind the listenfd and the datafd. */
    if (bind(listenfd, (struct sockaddr*)&server_cntl_addr, 
sizeof(server_cntl_addr)) < 0)
    {
        cout << FTP_LOG_HEAD << " Binding control port error!" << endl;
    }
    listen(listenfd, FTP_MAX_QUEUE);
    if (bind(datafd, (struct sockaddr*)&server_data_addr, 
sizeof(server_data_addr)) < 0)
    {
        cout << FTP_LOG_HEAD << " Binding data port error!" << endl;
    }
    listen(datafd, FTP_MAX_QUEUE);
    
    /* Server has been started. */
    socks.push_back(listenfd);
    socks.push_back(datafd);
    cout <<  FTP_LOG_HEAD << " Server is running!" << endl;
    
    /* Default mode is standard. */
    while(1)
    {
        int i;
        nfds = epoll_wait(epfd, events, FTP_MAX_QUEUE, 2000);
        //cout << "Events:" << nfds << endl;
        for(i = 0; i<nfds; i++)
        {
            int type;
            /* Listenfd starts working. */
            if (events[i].data.fd == listenfd)
            {
				char cfb[128];
                connfd = accept(listenfd, (struct sockaddr*)&client_addr, &c_len);
                /* Allocation is failed. */
                if (connfd < 0)
                {
                    cout << FTP_LOG_HEAD << " A client control connection failed: " << 
                        inet_ntoa(client_addr.sin_addr) << endl;
                    break;
                }
                set_no_blocking(connfd);
				const char *cfb_ptr = inet_ntop(AF_INET, &client_addr, cfb, sizeof(cfb));
                cout << FTP_LOG_HEAD << " Get a client control connection: " << cfb_ptr
                    << ", at: " << connfd << ", ready to read" << endl;
                clients[connfd].set_id(connfd);
                // Add the connfd to the socks set.
                socks.push_back(connfd);
                ev_cntl.data.fd = connfd;
                ev_cntl.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev_cntl);
                //cout << "Add it completely!" << endl;
            }
            else if (events[i].data.fd == datafd)
            {
                //cout << "Block here?" << endl;
                connfd = accept(datafd, (struct sockaddr*)&client_addr, &c_len);
                if (connfd < 0)
                {
                    cout << FTP_LOG_HEAD << " A client data connection failed: " << 
                        inet_ntoa(client_addr.sin_addr) << endl;
                    break;
                }
                set_no_blocking(connfd);
                cout << FTP_LOG_HEAD << "Get a client data connection: " << inet_ntoa(client_addr.sin_addr) << 
                    ":" << ntohs(client_addr.sin_port) << ", at: " << connfd << endl;
                seq[connfd] = 0;
                ev_data.data.fd = connfd;
                ev_data.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev_data);
            }
            /* Read events */
            else if (events[i].events & EPOLLIN)
            {
                //cout << "Catch a read event:" << sockfd << endl;
                if ((sockfd = events[i].data.fd) < 0) continue;
                /* This can be put into a function. */
                if (find(socks.begin(), socks.end(), sockfd) != socks.end())
                    type = FTP_CONTROL_TYPE;
                else
                    type = FTP_DATA_TYPE;
                while (1)
                {
                    int recvNum;
                    if (type == FTP_CONTROL_TYPE)
                    {
                        recvNum = read(sockfd, cmd, CMD_MAX_LENGTH);
                        //cout << "Recv:" << recvNum << endl;
                    }
                    else if (type ==  FTP_DATA_TYPE)
                    {
                        recvNum = read(sockfd, buffer[sockfd], FILE_MAX_BUFFER);
                        /* For futural features */
                        seq[sockfd] ++;
                    }
                    if (recvNum < 0)
                    {
                        /* FULL */
                        if (errno == EAGAIN) break;
                        else if (errno == ECONNRESET)
                        {
                            cout << FTP_LOG_HEAD << " " << sockfd << " get a RESET!" << endl;
                            close(sockfd);
                            /* Reaptable, may put them into a function in the future. */
                            if (type == FTP_CONTROL_TYPE)
                            {
                                clients[sockfd].reset();
                                for (iter = socks.begin(); iter != socks.end(); iter++)
                                {
                                    if (*iter ==  sockfd)
                                    {
                                        iter = socks.erase(iter);
                                        break;
                                    }
                                    else if (iter == socks.end())
                                        break;
                                }
                            }
                            else
                            {
                                seq[sockfd] = -1;
                                miter = data_feedback.begin();
                                while (miter !=  data_feedback.end())
                                {
                                    if (miter->first == sockfd)
                                    {
                                        // For safe programming!
                                        data_feedback.erase(miter++);
                                        break;
                                    }
                                }
                            }
                            //ev_data.data.fd=-1/ev_cntl.data.fd=-1
                            break;
                        }
                        else if (errno == EINTR) continue;
                        else
                        {
                            cout << FTP_LOG_HEAD << " " << sockfd << " is unrecoverable!" << endl;
                            close(sockfd);
                            if (type == FTP_CONTROL_TYPE)
                            {
                                clients[sockfd].reset();
                                for (iter = socks.begin(); iter != socks.end(); iter++)
                                {
                                    if (*iter ==  sockfd)
                                    {
                                        iter = socks.erase(iter);
                                        break;
                                    }
                                    else if (iter == socks.end())
                                        break;
                                }
                            }
                            else
                            {
                                seq[sockfd] = -1;
                                miter = data_feedback.begin();
                                while (miter !=  data_feedback.end())
                                {
                                    if (miter->first == sockfd)
                                    {
                                        // For safe programming!
                                        data_feedback.erase(miter++);
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                    else if (recvNum == 0)
                    {
                        cout << FTP_LOG_HEAD << " " << sockfd << " shuts down normally!" << endl;
                        close(sockfd);
                        if (type == FTP_CONTROL_TYPE)
                        {
                            clients[sockfd].reset();
                            for (iter = socks.begin(); iter != socks.end(); iter++)
                            {
                                if (*iter ==  sockfd)
                                {
                                    iter = socks.erase(iter);
                                    break;
                                }
                                else if (iter == socks.end())
                                    break;
                            }
                        }
                        else
                        {
                            seq[sockfd] = -1;
                            miter = data_feedback.begin();
                            while (miter !=  data_feedback.end())
                            {
                                if (miter->first == sockfd)
                                {
                                    // For safe programming!
                                    data_feedback.erase(miter++);
                                    break;
                                }
                            }
                        }
                    }
                    if (recvNum == CMD_MAX_LENGTH)
                    {
                        memset(feedback, 0, sizeof(feedback));
                        strcpy(feedback, (process_request(cmd, sockfd, type)).c_str());
                            
                        //cout << "GET A FEEDBACK:" << feedback << endl;
                        strcpy(clients[sockfd].last_feedback, feedback);
                        break;
                    }
                    else if (recvNum == FILE_MAX_BUFFER)
                    {
                        data_feedback.insert(map<int, string>::value_type(sockfd, 
                            process_request(buffer[sockfd], sockfd, type)));
                        //cout << "Get file transportation! --" << buffer[sockfd] << endl;
                        break;
                    }
                    else
                    {
                        close(sockfd);
                        if (type == FTP_CONTROL_TYPE)
                        {
                            clients[sockfd].reset();
                            for (iter = socks.begin(); iter != socks.end(); iter++)
                            {
                                if (*iter ==  sockfd)
                                {
                                    iter = socks.erase(iter);
                                    break;
                                }
                                else if (iter == socks.end())
                                    break;
                            }
                        }
                        else
                        {
                            seq[sockfd] = -1;
                            miter = data_feedback.begin();
                            while (miter !=  data_feedback.end())
                            {
                                if (miter->first == sockfd)
                                {
                                    // For safe programming!
                                    data_feedback.erase(miter++);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                if (type == FTP_CONTROL_TYPE)
                {
                    ev_cntl.data.fd = sockfd;
                    ev_cntl.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev_cntl);
					cout << FTP_LOG_HEAD << " " << sockfd << " is ready to write." << endl;
                }
                else
                {
                    ev_data.data.fd = sockfd;
                    ev_data.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev_data);
                }
            }
            /* Write events */
            else if (events[i].events & EPOLLOUT)
            {
                sockfd = events[i].data.fd;
                if (find(socks.begin(), socks.end(), sockfd) != socks.end())
                    type = FTP_CONTROL_TYPE;
                else
                    type = FTP_DATA_TYPE;
                if (type == FTP_CONTROL_TYPE)
                {
                    write(sockfd, clients[sockfd].last_feedback, FB_MAX_LENGTH);
                    ev_cntl.data.fd = sockfd;
                    ev_cntl.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev_cntl);
                }
                else
                {
                    // TODO--FILE TRANSFORMATION
                    write(sockfd, buffer[sockfd], FILE_MAX_BUFFER);
                    ev_data.data.fd = sockfd;
                    ev_data.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev_data);
                }
                    
            }
        }
    }
   
	return 0;
}

/* Set the socket with the flag O_NONBLOCK */
void set_no_blocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);
	if(opts < 0)
	{
		cerr << "Get sock options error!" << endl;
		exit(1);
	}
	opts |= O_NONBLOCK;
	if(fcntl(sock, F_SETFL, opts) < 0)
	{
		cerr << "Set sock options error!" << endl;
		exit(1);
	}
}

/* Process the requests from the clients, and return the feedback */
string process_request(char* p_cmd, int sock, int type)
{
    string rt;
    string rcmd;                                            // REAL CMD
    string args;
    if (type ==  FTP_CONTROL_TYPE)
    {
        cout << FTP_LOG_HEAD << " Get a control cmd: " << p_cmd << ", at " << sock << endl;
        int i;
        for (i = 0; i<CMD_MAX_LENGTH; i++)
        {
            if (p_cmd[i] != ' ' && p_cmd[i] != '\0' && p_cmd[i] != '\n')
                rcmd += p_cmd[i];
            else
                break;
        }
        for (int j = i+1; j<CMD_MAX_LENGTH; j++)
        {
            if (p_cmd[j] != '\0' && p_cmd[i] != '\n')
                args += p_cmd[j];
            else
                break;
        }
        //cout << "REAL CMD:" << rcmd << ", args:" << args <<  endl;
        if (rcmd == FTP_CMD_USER)
        {
            /* Request a password */
            rt = FTP_RSP_R_PASS;
            strcpy(clients[sock].user, rcmd.c_str());
        }
        else if (rcmd == FTP_CMD_PASS)
        {
            /* Get the user, then match them. */
            /* In the future, this should be put into the database. */
            if (args == "super123")
            {
                clients[sock].is_logged = true;
                clients[sock].set_password(args.c_str());
                rt = FTP_RSP_P_PASS;
            }
            else
                rt = FTP_RSP_E_PASS;
        }
        else if (rcmd == FTP_CMD_LIST)
        {
            if (clients[sock].is_logged)
            {
                rt = FTP_RSP_LIST;
                DIR* dir;
                struct dirent* ptr;
                dir = opendir(FTP_DIR);
                while ((ptr = readdir(dir)) != NULL)
                {
                    /* Strcmp will return a true value while dismatching. */
                    #ifdef __linux
                    if (!strcmp(ptr->d_name, "."))
                        continue;
                    else if (!strcmp(ptr->d_name, ".."))
                        continue;
                    struct stat file_stat;
                    string file_path(FTP_DIR);
                    file_path += ptr->d_name;
                    stat(file_path.c_str(), &file_stat);
                    rt += ptr->d_type;
                    rt += " ";
                    rt += ptr->d_name;
                    string temp;
                    temp += ptr->d_type;
                    temp += " ";
                    temp += ptr->d_name;
                    // TODO-- This place, the file name may be greater than 50 place.
                    for (int pos = temp.length(); pos<40; pos++)
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
        else if (rcmd == FTP_CMD_PUT)
        {
            if (clients[sock].is_logged)
            {
                rt = FTP_RSP_RF_START;
                string file_path(FTP_DIR);
                file_path += args;
                //strcpy(file_name[sock], args.c_str());        --real use
                strcpy(file_name_temp, args.c_str());
                //ofs[sock].open(file_path.c_str(), ios::binary);
                ofs_temp.open(file_path.c_str(), ios::binary);
            }
            else
                rt = FTP_RSP_R_LOG;
        }
        else if (rcmd == FTP_CMD_GET)
        {
            if (clients[sock].is_logged)
            {
                rt = FTP_RSP_SF_START;
                string file_path(FTP_DIR);
                file_path += args;
                //strcpy(file_name[sock], args.c_str());
                strcpy(file_name_temp, args.c_str());
                //ifs[sock].open(file_path.c_str(), ios::binary);
                // TODO--judge whether the file exists.
                ifs_temp.open(file_path.c_str(), ios::binary);
            }
            else
                rt = FTP_RSP_R_LOG;
        }
        else if (rcmd == FTP_CMD_QUIT)
        {
            rt = FTP_RSP_BYE;
        }
        else
            rt = FTP_RSP_ERR;
        return rt;
    }
    else
    {
        //  p_cmd = buffer
        if (p_cmd[0] == FTP_FTR_CMD_CONTINUE)
        {
            rt = FTP_FTR_CMD_CONTINUE;
            cout << FTP_LOG_HEAD << "Write into " << file_name_temp << ", size of " << strlen(p_cmd)-1 << endl;
            /* More comman way, but it need to be tested for binary and ascii! */
            int b_len = strlen(p_cmd);
            for (int d = 1; d<b_len; d++)
                ofs_temp.put(p_cmd[d]);
        }
        else if (p_cmd[0] == FTP_FTR_CMD_ENDALL)
        {
            rt = FTP_FTR_CMD_ENDALL;
            memset(p_cmd, 0, sizeof(p_cmd));
            strcpy(file_name[sock], "");
            strcpy(file_name_temp, "");
            //ofs[sock].close();
            ofs_temp.close();
        }
        /* Sending files would return the file data. */
        else if (p_cmd[0] == FTP_FTS_CMD_CONTINUE)
        {
            /* Just like writing */
            ifs_temp.read(buffer[sock]+1, sizeof(buffer[sock])-1);
            /* Get the file ending, gcount() is not useful for now. */
            int real_read = ifs_temp.gcount();
            if (real_read < FILE_MAX_BUFFER)
            {
                rt = FTP_FTS_CMD_ENDALL;
                buffer[sock][0] = FTP_FTS_CMD_ENDALL;
            }
            else
            {
                rt = FTP_FTS_CMD_CONTINUE;
                buffer[sock][0] = FTP_FTS_CMD_CONTINUE;
            }
            cout << FTP_LOG_HEAD << "Read from " << file_name_temp << ", size of " << real_read << endl;
            // For future features
            rt.append(p_cmd+1);
        }
        else if (p_cmd[0] == FTP_FTS_CMD_ENDALL)
        {
            rt = FTP_FTS_CMD_ENDALL;
            memset(p_cmd, 0, sizeof(p_cmd));
            strcpy(file_name[sock], "");
            strcpy(file_name_temp, "");
            //ifs[sock].close();
            ifs_temp.close();
        }
        else
        {
            /* Breakpoint resends, and errors handle in the future. */
            rt = FTP_FT_ERR;
        }
        return rt;
    }
}

/* Change the file size to a human-readable format. */
string byte2std(int size)
{
    string result;
    char std[31];
    if (size >= 1024)
    {
        sprintf(std, "%g", (double)(size/1024));
        result = std;
        result += "KB";
    }
    else
    {
        sprintf(std, "%d", size);
        result = std;
        result += "B";
    }
    return result;
}
