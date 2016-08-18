/*
 * User Client Simple Implement
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>                   /* For future human-friendly format */ 
#include <netinet/in.h>					/* Contains relative structs about AF_INET */
#include <arpa/inet.h>					/* Contains relative functions about AF_INET */
#include <unistd.h>

#define _FTP_SERVER_PORT 21
#define _FTP_DATA_PORT 20
#define CMD_MAX_LENGTH 128
#define FB_MAX_LENGTH 512
#define FILE_MAX_BUFFER 2500
#define SHELL_HAED "ftp> "
#define _FTP_CLINET_QUIT "Quit"
#define VERSION "1.1"

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <boost/thread/thread.hpp>
using namespace std;

void print_server_info()
{
	time_t tt;
	time(&tt);
	cout << "+------------------------------+" << endl;
	cout << "+ " << ctime(&tt);
    cout << "+ FTP Server v" << VERSION << endl;
    cout << "+ Freedom and Welcome!" << endl;
	cout << "+------------------------------+" << endl;
}

void thread_parallel_test(int num)
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = _FTP_SERVER_PORT;
	if (connect(sfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		cerr << "Connect to server failed : thread " << num << endl;
		return;
	}
	string cmd = "List";
	int ret = send(sfd, cmd.c_str(), CMD_MAX_LENGTH, 0);
	cout << "Thread " << num << ": send " << ret << endl;
	close(sfd);
}

int main()
{
    /* Variables */
    struct sockaddr_in addr;
    int sockfd;
    int len;
    int state;
    int sock_on_server;
    char cmd[CMD_MAX_LENGTH] = "IM A USER";
    char feedback[FB_MAX_LENGTH];
    char buffer[FILE_MAX_BUFFER];
    
    /* Socket settings */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_aton("49.140.62.120", &addr.sin_addr); -- real use
    addr.sin_port = htons(_FTP_SERVER_PORT);
    

	/* Parallel Test */
    /*
	boost::thread_group tg;
	for (int i=0; i<200; i++) {
		boost::thread td(boost::bind(&thread_parallel_test, i));
		tg.add_thread(&td);
		cout << "Thread " << i << " is running..." << endl;
	}
	tg.join_all();
    */
    
    /* Start connecting to the server */
    len = sizeof(addr);
    state = connect(sockfd, (struct sockaddr*)&addr, len);
    if(state == -1)
    {
        cerr << "Connection is failed!" << endl;
        return 1;
    }
    
    /* Send and receive the data */
    print_server_info();
    
    /* Negotiate withe the server */
    char nego[5];
    read(sockfd, nego, sizeof(nego));
    if (nego[0] == 0x15)
        sock_on_server = atoi(nego+1);
    
	/* Usage: 'cmd arg' */ 
    string rcmd = "DFLT";
    string args = "NONE";
    while(rcmd != _FTP_CLINET_QUIT)
    {
        memset(cmd, '\0', sizeof(cmd));
        rcmd = "";
        args = "";
        cout << SHELL_HAED;
        cin.getline(cmd, CMD_MAX_LENGTH);

		transform(cmd, cmd+strlen(cmd), cmd, ::toupper);
		transform(cmd+1, cmd+strlen(cmd), cmd+1, ::tolower);

		int i;
        for(i=0; i<CMD_MAX_LENGTH; i++)
        {
            if(cmd[i] != ' ' && cmd[i] != '\0' && cmd[i] != '\n')
                rcmd += cmd[i];
            else
                break;
        }
        for(int j=i+1; j<CMD_MAX_LENGTH; j++)
        {
            if(cmd[j] != '\0' && cmd[j] != '\n')
                args += cmd[j];
            else
                break;
        }

        // string.substr is a alternate method.
        //cout << "sock " << sockfd << ": " << rcmd << ", " << args << endl;
		if(rcmd != "Get" && rcmd != "Put")
		{
        	int ret = send(sockfd, cmd, CMD_MAX_LENGTH, 0);
#ifdef DEBUG
		cout << "Send to the server: " << ret << endl;
#endif
			if (ret < 0) {
				cerr << "The server is closed for you now....." << endl;
				exit(1);
			}
       	 	ret = recv(sockfd, feedback, FB_MAX_LENGTH, 0);
			/* Judge the situations in the future! */
			if (ret == 0)
				break;

            if(feedback[0] == 0x01)
            {
                /* Get password! */
                memset(cmd, 0, sizeof(cmd));
                strcat(cmd, "Pass ");
                string password = getpass("Password(4~15):");
                int ps_len = password.length();
                strcat(cmd+5, password.c_str());
                /* Authorized or not from the server response! */
                if(ps_len >=4 && ps_len <= 15)
                {
                    send(sockfd, cmd, CMD_MAX_LENGTH, 0);
                    memset(feedback, 0, FB_MAX_LENGTH);
                    recv(sockfd, feedback, FB_MAX_LENGTH, 0);
                    if(feedback[0] == 0x02)
                        cout << "Authorized!" << endl;
                    else if(feedback[0] == 0x03)
                        cout << "Wrong password!" << endl;
					else {
						cout << "An exception occurs, please report this!" << endl;
					}
                }
                else
                    cout << "Invalid input!" << endl;
            }
            else if(feedback[0] == 0x04)
            {
                /* List the server dir. */
                int i;
				cout << "+--------------------------------------------------------+" << endl;
                cout << "++ Server Files:" << endl;
                cout << feedback+1;
				cout << "+--------------------------------------------------------+" << endl;
            }
            else if(feedback[0] == 0x08)
            {
                cout << "You are not authorized." << endl;
                cout << "Please log in the server!" << endl;
            }
            else if(feedback[0] == 0x09)
            {
                cout << "Invalid commands!(You can type 'Help' to list the commands)" << endl;
            }
            else if(feedback[0] == 0x10)
            {
                /* So the client will quit. */
				break;
            }
			else
			{
				cout << "Unknown error!" << endl;
			}
		}
		else
		{
            /* Create a data link */
            int datafd;
            datafd = socket(AF_INET, SOCK_STREAM, 0);
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
            //inet_aton("49.140.62.120", &addr.sin_addr);
            addr.sin_port = htons(_FTP_DATA_PORT);
            len = sizeof(addr);
            state = connect(datafd, (struct sockaddr*)&addr, len);
            if(state == -1)
            {
                cerr << "Cannot create the data link, please report this problem or retry!" << endl;
                continue;
            }
            
            /* Mapping the data link with the control link on the server */
            char contact[5];
            contact[0] = 0x15;
            snprintf(contact+1, sizeof(contact)-1, "%d", sock_on_server);
            send(datafd, contact, sizeof(contact), 0);
            
            /* Send or tell the start action with the control link. */
            send(sockfd, cmd, CMD_MAX_LENGTH, 0);
            recv(sockfd, feedback, FB_MAX_LENGTH, 0);
            
            memset(buffer, 0, sizeof(buffer));
            if(feedback[0] == 0x05)
            {
                ifstream ifs;
                ifs.open(args.c_str());
                if(!ifs)
                {
                    cout << "Not a invalid file name, please check it!" << endl;
                    buffer[0] = 0x13;
                    send(datafd, buffer, 1, 0);
                    memset(buffer, 0, sizeof(buffer));
                    recv(datafd, buffer, 1, 0);
                }
                else
                {
					//int send_num = FILE_MAX_BUFFER;
                    while(!ifs.eof())
                    {
                        ifs.read(buffer+1, sizeof(buffer)-1);
						if (ifs.eof())
							buffer[0] = 0x13;
						else
							buffer[0] = 0x11;
                        int sd_num = send(datafd, buffer, (ifs.gcount()+1), 0);
                        memset(buffer, 0, sizeof(buffer));
                    }
                    if(buffer[0] == 0x20)
                    {
                        cout << "Occur an error while file sending, please try it again." << endl;
                        /* TODO -- ERROR CHECKS */
                    }
                    else
                    {
                        /* Handle the tail as an active end. */
                        memset(buffer, 0, sizeof(buffer));
                        if (recv(datafd, buffer, 1, 0) && buffer[0] == 0x13)
                        	cout << args << "  ---->  Server" << "  [OK]" << endl;
						else
							cout << "Get an error when transferring completed." << endl;
                    }
                    ifs.close();
                }
            }
            else if(feedback[0] == 0x06)
            {
                ofstream ofs;
                ofs.open(args.c_str());
                if(!ofs)
                {
                    cout << "Occur an error while file creating, please check it!" << endl;
                    buffer[0] = 0x14;
                    send(datafd, buffer, 1, 0);
                    memset(buffer, 0, sizeof(buffer));
                    recv(datafd, buffer, 1, 0);
                }
                else
                {
					int b_len = FILE_MAX_BUFFER;
					/* Multiple conditions to judge the end! */
                    while(b_len == FILE_MAX_BUFFER && buffer[0] != 0x14 && buffer[0] != 0x20)
                    {
						memset(buffer, 0, sizeof(buffer));
                        b_len = recv(datafd, buffer, FILE_MAX_BUFFER, 0);
                        ofs.write(buffer+1, b_len-1);
                    }
                    if(buffer[0] == 0x20)
                    {
                        cout << "Occur an error while file receiving, please try it again." << endl;
                        /* TODO -- ERROR REPAIRING. */
                    }
                    else
                    {
                        /* Handle the tail as a passive end. */
                        buffer[0] = 0x14;
                        send(datafd, buffer, 1, 0);
                        cout << "Server  ---->  " << args << "  [OK]" << endl;
                    }
                    ofs.close();
                }
            }
            else if(feedback[0] == 0x08)
            {
                cout << "You are not authorized." << endl;
                cout << "Please log in the server!" << endl;
            }
            close(datafd);
		}
    }
    close(sockfd);
    cout << "Bye!" << endl;
    return 0;
}
