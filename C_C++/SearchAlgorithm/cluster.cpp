#include <iostream>
#include <cstdlib>
#ifndef __STRING__
#include <string>
#include <vector>
#include <map>
#endif
using namespace std;

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "cluster_config.h"

extern vector<string> query(string);

void set_no_blocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);
	if(opts < 0)
	{
		cerr << "Get sock options error:" << sock << "!" << endl;
		exit(1);
	}
	opts |= O_NONBLOCK;
	if(fcntl(sock, F_SETFL, opts) < 0)
	{
		cerr << "Set sock options error:" << sock << "!" << endl;
		exit(1);
	}
}

void run_as_a_master()
{
	int listenfd, sockfd, epfd;
	int nfds;
	struct epoll_event ev, events[MAX_SLAVE];
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	char buffer[BUF_MAX_LEN];
	socklen_t client_len;
	map<int, string> slaves;
	int slave_id = 1;
	
	/* Initialize */
	epfd = epoll_create(MAX_SLAVE);
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	set_no_blocking(listenfd);

	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = MASTER_PORT;

	if(bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		cerr << "Bind the port error!" << endl;
	listen(listenfd, MAX_SLAVE);

	cout << "Master node has been established!" << endl;
	//cout << "You can publish tasks now!" << endl;
	string input;
	vector<string> result;
	vector<string>::iterator it;
	while(1)
	{
		getline(cin, input);
		result = query(input);
		for(it = result.begin(); it != result.end(); it++)
			cout << "From Master: " << *it << endl;

		int i;
		nfds = epoll_wait(epfd, events, MAX_SLAVE, WAIT_DELAY_TIME);
		for(i=0; i<nfds; i++)
		{
			if(events[i].data.fd == listenfd)
			{
				sockfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_len);
				if(sockfd < 0)
					cerr << "A client connection has failed!" << endl;

				set_no_blocking(sockfd);
				ev.data.fd = sockfd;
				ev.events = EPOLLOUT | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

				/* map the slave with the sockfd */
				string idfr = "Slave";
				idfr += ' ';
				idfr += slave_id;
				slaves[sockfd] = idfr;
				slave_id ++;
			}
			else if(events[i].events & EPOLLIN)
			{
				if((sockfd=events[i].data.fd) < 0) continue;
				while(1)
				{
					int recvNum = read(sockfd, buffer, BUF_MAX_LEN);
					if(recvNum < 0)
					{
						if(errno == EAGAIN) break;
						else if(errno == ECONNRESET)
						{
							close(sockfd);
							ev.data.fd = -1;
							cout << slaves[sockfd] << " gets a RST!" << endl;
							break;
						}
						else if(errno == EINTR) continue;
						else
						{
							close(sockfd);
							ev.data.fd = -1;
							cout << slaves[sockfd] << " is unrecoverable!" << endl;
							break;
						}
					}
					else if(0 == recvNum)
					{
						close(sockfd);
						ev.data.fd = -1;
						cout << slaves[sockfd] << " shuts down normally!" << endl;
					}
					else if(BUF_MAX_LEN == recvNum)
					{
						if(buffer[0] == 0x01)
						{
							cout << "From " << slaves[sockfd] << ": " << buffer+1 << endl;
							continue; 
						}
						else if(buffer[0] == 0x10)
						{
							cout << "From " << slaves[sockfd] << ": " << buffer+1 << endl;
							break;
						}
					}
					else
					{
						close(sockfd);
						ev.data.fd = -1;
						break;
					}
				}
				ev.data.fd = sockfd;
				ev.events = EPOLLET | EPOLLOUT;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
			else if(events[i].events & EPOLLOUT)
			{
				sockfd = events[i].data.fd;
				write(sockfd, input.c_str(), sizeof(input.c_str()));
				cout << "Master has published a task to " << slaves[sockfd] << "." << endl;
				/* change the ev to do read jobs. */
				ev.data.fd = sockfd;
				ev.events = EPOLLET | EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
		}
	}
		
}

void run_as_a_slave()
{
	/* TODO this */
}
