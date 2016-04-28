#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>                   /* For future human-friendly format */ 
#include <netinet/in.h>					/* Contains relative structs about AF_INET */
#include <arpa/inet.h>					/* Contains relative functions about AF_INET */
#include <unistd.h>

#define _FTP_SERVER_PORT 21
#define _FTP_DATA_PORT 20
#define CMD_MAX_LENGTH 127
#define FB_MAX_LENGTH 127
#define FILE_MAX_BUFFER 1024
#define SHELL_HAED "ftp>"
#define _FTP_CLINET_QUIT "Quit"

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

void print_server_info()
{
    cout << "FTP Server v1.0" << endl;
    cout << "Freedom and Welcome!" << endl;
}

int main()
{
    /* Variables */
    struct sockaddr_in addr;
    int sockfd;
    int len;
    int state;
    char cmd[CMD_MAX_LENGTH] = "IM A USER";
    char feedback[FB_MAX_LENGTH];
    char buffer[FILE_MAX_BUFFER];
    
    /* Socket settings */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_aton("49.140.62.120", &addr.sin_addr); -- real use
    addr.sin_port = _FTP_SERVER_PORT;
    
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
    string rcmd = "DFLT";
    string args = "NONE";
    while(rcmd != _FTP_CLINET_QUIT)
    {
        memset(cmd, '\0', sizeof(cmd));
        rcmd = "";
        args = "";
        cout << SHELL_HAED;
        cin.getline(cmd, CMD_MAX_LENGTH);
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
        //cout << "str: " << rcmd << ", " << args << endl;
		if(rcmd != "Get" && rcmd != "Put")
		{
        	send(sockfd, cmd, CMD_MAX_LENGTH, 0);
       	 	recv(sockfd, feedback, FB_MAX_LENGTH, 0);
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
                }
                else
                    cout << "Invalid input!" << endl;
            }
            else if(feedback[0] == 0x04)
            {
                /* List the server dir. */
                int i;
                cout << "- - Server Files:" << endl;
                cout << feedback+1;
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
            addr.sin_port = _FTP_DATA_PORT;
            len = sizeof(addr);
            state = connect(datafd, (struct sockaddr*)&addr, len);
            if(state == -1)
            {
                cerr << "Cannot create the data link, please report this problem or retry!" << endl;
                continue;
            }
            
            /* Send or tell the start action. */
            send(sockfd, cmd, CMD_MAX_LENGTH, 0);
            recv(sockfd, feedback, CMD_MAX_LENGTH, 0);
            
            memset(buffer, 0, sizeof(buffer));
            if(feedback[0] == 0x05)
            {
                ifstream ifs;
                ifs.open(args.c_str(), ios::binary);
                if(!ifs)
                {
                    cout << "Not a invalid file name, please check it!" << endl;
                    buffer[0] = 0x13;
                    send(datafd, buffer, FILE_MAX_BUFFER, 0);
                    memset(buffer, 0, sizeof(buffer));
                    recv(datafd, buffer, FILE_MAX_BUFFER, 0);
                }
                else
                {
                    while(!ifs.eof())
                    {
                        buffer[0] = 0x11;
                        ifs.read(buffer+1, sizeof(buffer)-1);
                        send(datafd, buffer, FILE_MAX_BUFFER, 0);
                        memset(buffer, 0, sizeof(buffer));
                        recv(datafd, buffer, FILE_MAX_BUFFER, 0);
                        if(buffer[0] != 0x11)
                            break;
                    }
                    if(buffer[0] == 0x20)
                    {
                        cout << "Occur an error while file sending, please try it again." << endl;
                    }
                    else
                    {
                        /* Handle the tail. */
                        buffer[0] = 0x13;
                        send(datafd, buffer, FILE_MAX_BUFFER, 0);
                        memset(buffer, 0, sizeof(buffer));
                        recv(datafd, buffer, FILE_MAX_BUFFER, 0);
                        cout << args << "  ---->  Server" << "  [OK]" << endl;
                    }
                    ifs.close();
                }
            }
            else if(feedback[0] == 0x06)
            {
                ofstream ofs;
                ofs.open(args.c_str(), ios::binary);
                if(!ofs)
                {
                    cout << "Occur an error while file creating, please check it!" << endl;
                    buffer[0] = 0x14;
                    send(datafd, buffer, FILE_MAX_BUFFER, 0);
                    memset(buffer, 0, sizeof(buffer));
                    recv(datafd, buffer, FILE_MAX_BUFFER, 0);
                }
                else
                {
                    while(buffer[0] != 0x14)
                    {
                        buffer[0] = 0x12;
                        send(datafd, buffer, FILE_MAX_BUFFER, 0);
                        memset(buffer, 0, sizeof(buffer));
                        recv(datafd, buffer, FILE_MAX_BUFFER, 0);
                        int b_len = strlen(buffer);
                        for (int d = 1; d<b_len; d++)
                            ofs.put(buffer[d]);
                    }
                    if(buffer[0] == 0x20)
                    {
                        cout << "Occur an error while file receiving, please try it again." << endl;
                    }
                    else
                    {
                        /* Handle the tail. */
                        buffer[0] = 0x14;
                        send(datafd, buffer, FILE_MAX_BUFFER, 0);
                        memset(buffer, 0, sizeof(buffer));
                        recv(datafd, buffer, FILE_MAX_BUFFER, 0);
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
