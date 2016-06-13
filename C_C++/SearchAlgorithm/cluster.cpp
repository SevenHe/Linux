#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring> 		/* for memset */
#ifndef __STRING__
#include <string>
#include <thread>
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
	clock_t start, finish;
	while(1)
	{
		start = clock();
		cout << "Search: ";
		getline(cin, input);
		thread master_job([&](){
			result = query(input);
			for(it = result.begin(); it != result.end(); it++)
				cout << "From Master: " << *it << endl;
		});
		/* we need not to wait it. */
		//master_job.join();

	  /* iterate the node set */
	  while(1)
	  {
		int i;
		/* just for one node, if we need more, extend the is_complete as a vector. */
		bool is_complete = false;
		nfds = epoll_wait(epfd, events, MAX_SLAVE, WAIT_DELAY_TIME);
		//cout << "event: " << nfds << endl;
		//cout << "events.fd: " << events[0].data.fd << endl;
		//cout << "listenfd: " << listenfd << endl;
		if(0 == nfds)
			break;
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
				stringstream ss;
				ss << "Slave " << slave_id;
				slaves[sockfd] = ss.str();
				
				cout << "Assign " << slaves[sockfd] << " at fd " << sockfd << "." << endl;
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
							is_complete = true;
							break;
						}
						else if(errno == EINTR) continue;
						else
						{
							close(sockfd);
							ev.data.fd = -1;
							cout << slaves[sockfd] << " is unrecoverable!" << endl;
							cout << "So the task is cancelled!" << endl;
							is_complete = true;
							break;
						}
					}
					else if(0 == recvNum)
					{
						close(sockfd);
						ev.data.fd = -1;
						cout << slaves[sockfd] << " shuts down normally!" << endl;
						cout << "So the task is cancelled!" << endl;
						is_complete = true;
						break;
					}
					else if(BUF_MAX_LEN == recvNum)
					{
						if(buffer[0] == SLAVE_DATA)
						{
							cout << "From " << slaves[sockfd] << ": " << buffer+1 << endl;
							continue; 
						}
						else if(buffer[0] == SLAVE_LAST_DATA)
						{
							cout << "From " << slaves[sockfd] << ": " << buffer+1 << endl;
							is_complete = true;
							break;
						}
					}
					else
					{
						close(sockfd);
						ev.data.fd = -1;
						is_complete = true;
						break;
					}
				}
				if(is_complete)
				{
					ev.data.fd = sockfd;
					ev.events = EPOLLET | EPOLLOUT;
					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
				}
			}
			else if(events[i].events & EPOLLOUT)
			{
				sockfd = events[i].data.fd;
				int ret = write(sockfd, input.c_str(), sizeof(input.c_str()));
				if(ret > 0)
					cout << "Master has published a task to " << slaves[sockfd] << "." << endl;
				/* change the ev to do read jobs. */
				ev.data.fd = sockfd;
				ev.events = EPOLLET | EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
		}
		/* A serach is complete. */ 
		if(is_complete)
			break;
	  }
	  master_job.join();
	  finish = clock();
	  cout << "Elapsed Time: " << double(finish-start)*1000/CLOCKS_PER_SEC << "ms." << endl;
	  cout << endl;
	}
		
}

void run_as_a_slave()
{
	int serverfd,len;
	struct sockaddr_in server_addr;
	char buffer[BUF_MAX_LEN];
	vector<string> query_result;
	vector<string>::iterator it;
	vector<string>::iterator tmp;
	
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = MASTER_PORT;	

	if(connect(serverfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		cerr << "Connect to the master node error!" << endl;
		cout << "Please check the configuration." << endl;
		exit(1);
	}
	else
		cout << "The connection to the master has been established!" << endl;	
	
	while(1)
	{
		memset(buffer, 0, BUF_MAX_LEN);
		recv(serverfd, buffer, BUF_MAX_LEN, 0);
		cout << "From Master: get the task -- " <<  buffer << endl;
		query_result = query(buffer);
		for(it = query_result.begin(); it != query_result.end(); it++)
		{
			memset(buffer, 0, BUF_MAX_LEN);
			tmp = it;
			if((++tmp) != query_result.end())
				buffer[0] = SLAVE_DATA;
			else
				buffer[0] = SLAVE_LAST_DATA;
			strcat(buffer+1, (*(it)).c_str());
			/* TODO- to check the security and completeness in the future */
			len = send(serverfd, buffer, BUF_MAX_LEN, 0);
			cout << "Send " << len << "B to Master: " << buffer << endl;
		}
	}

}
