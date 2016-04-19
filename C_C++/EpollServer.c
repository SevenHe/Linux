#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 32
#define OPEN_MAX 100
#define MAX_THREAD 16
#define LISTENQ 20
#define PORT 5555

// for future features
struct thread_info {
	pthread_t thread_id;
	int thread_num;
};

struct thread_info thread_info[MAX_THREAD];

// a thread to do epoll bussiness
void *business_worker(void*);

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

void init_a_thread_in_pool(int trd)
{
	thread_info[trd].thread_num = trd;
	int rs = pthread_create(&thread_info[trd].thread_id, NULL, business_worker, &thread_info[trd].thread_num);
	if(rs)
	{
		printf("ERROR: result code is %d.\n", rs);
	}
}

void normal_exit(int signal)
{
	exit(0);
}

int listenfd, connfd, sockfd, epfd, nfds;
char line[MAXLINE];
char feedback[MAXLINE] = "Thank you!";
struct epoll_event ev, events[20];
struct sockaddr_in client_addr;
struct sockaddr_in server_addr;
socklen_t client_len;
// create more for explicit control in the future
pthread_mutex_t business_worker_mutex[MAX_THREAD];

int main()
{
	int i;
	signal(SIGPIPE, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, &normal_exit);
	epfd = epoll_create(256);	// size can be whatever you like
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

	//srand((unsigned)time(NULL));
	printf("server is waiting..\n");
	while(1)
	{
		nfds = epoll_wait(epfd, events, 20, 1500);
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
						pthread_mutex_init(&business_worker_mutex[sockfd % 16], NULL);
						// there should be more complex judgement to ensure whether it is a task or not
						init_a_thread_in_pool(sockfd % 16);
						// if blocking, should handle the data and return the result
						// but a good way is every business worker has its own mutex lock.
						// and set a callback, if the data has been handled,  return it
						printf("Get a msg: %s\n", line);
						if(line[30] == '\0') 
						{
							memset(line, '\0', MAXLINE);
							break;
						}
						else continue;
					}
					else
					{
						close(sockfd);
						ev.data.fd = -1;
						break;
					}	
					printf("outer: Get a msg: %s\n", line);
				}
				ev.data.fd = sockfd;
				ev.events = EPOLLOUT | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
			else if(events[i].events & EPOLLOUT)
			{
				sockfd = events[i].data.fd;
				//pthread_mutex_lock(&business_worker_mutex[sockfd % 16]);
				write(sockfd, feedback, sizeof(feedback));
				printf("send a msg: %s\n", feedback);
				//设置用于读操作的文件描述符
				ev.data.fd = sockfd;
				//设置用于register的读操作事件
				ev.events = EPOLLIN | EPOLLET;
				//修改sockfd上要处理的事件为EPOLIN
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
				//pthread_mutex_unlock(&business_worker_mutex[sockfd % 16]);

			}
		}
	}
}

// restrict as void*
void *business_worker(void* trdId)
{
	pthread_mutex_lock(&business_worker_mutex[(int)(*(int*)(trdId))]);

	printf("Thread %d is working...\n", (int)(*(int*)(trdId)));
	sleep(1);
	printf("Thread %d: do some business logic...\n", (int)(*(int*)(trdId)));
	sleep(3);
	printf("Thread %d: have done!!\n", (int)(*(int*)(trdId)));

	pthread_mutex_unlock(&business_worker_mutex[(int)(*(int*)(trdId))]);
}

