#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAXLINE 32
#define OPEN_MAX 100
#define LISTENQ 20
#define PORT 5555

void setnoblocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);
	if(opts < 0)
	{
		perror("Get socket options error!\n");
		exit(1);
	}
	opts = opts|O_NONBLOCK;
	if(fcntl(sock, F_SETFL, opts) < 0)
	{
		perror("Set socket flags error!\n");
		exit(1);
	}
}

int main()
{
	int i, maxi, listenfd, connfd, sockfd, epfd, nfds;
	char line[MAXLINE];
	char feedback[MAXLINE] = "Thank you!";
	socklen_t client_len;
	struct epoll_event ev, events[20];
	epfd = epoll_create(256);	// size can be whatever you like

	struct sockaddr_in client_addr;
	struct sockaddr_in server_addr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	setnoblocking(listenfd);
	// set the fd to be handled
	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;

	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = PORT;

	bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	listen(listenfd, LISTENQ);

	maxi = 0;
	printf("server is waiting..\n");
	for( ; ; )
	{
		nfds = epoll_wait(epfd,  events, 20, 500);
		for(i=0; i<nfds; i++)
		{
			if(events[i].data.fd == listenfd)
			{
				connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_len);
				if(connfd < 0)
				{
					perror("connfd < 0!");
					exit(1);
				}
				setnoblocking(connfd);
				printf("Get a connection at: %d\n", connfd);
				ev.data.fd = connfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
			}
			// in or out is interchanging!
			else if(events[i].events & EPOLLIN)
			{
				if ((sockfd = events[i].data.fd) < 0) continue;
				while(1)
				{
					int recvNum = read(sockfd, line, MAXLINE);
					if(recvNum < 0)
					{
						if(errno == EAGAIN) break;
						else if(errno == ECONNRESET)
						{
							close(sockfd);
							ev.data.fd = -1;
							printf("Get a RST!\n");
							break;
						}
						else if(errno == EINTR) continue;
						else
						{
							close(sockfd);
							ev.data.fd = -1;
							printf("unrecoverable!\n");
							break;
						}
					}
					else if(recvNum == 0)
					{
						close(sockfd);
						ev.data.fd = -1;
						printf("shut down normally!\n");
					}
					if(recvNum == MAXLINE) 
					{
						printf("Get a msg: %s\n", line);
						continue;
					}
					else
					{
						close(sockfd);
						ev.data.fd = -1;
						break;
					}	
				}
				ev.data.fd = sockfd;
				ev.events = EPOLLOUT | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
			else if(events[i].events & EPOLLOUT)
			{
				sockfd = events[i].data.fd;
				write(sockfd, feedback, sizeof(feedback));
				printf("send a msg: %s\n", feedback);
				//设置用于读操作的文件描述符
				ev.data.fd = sockfd;
				//设置用于register的读操作事件
				ev.events = EPOLLIN | EPOLLET;
				//修改sockfd上要处理的事件为EPOLIN
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
		}
	}			
}
