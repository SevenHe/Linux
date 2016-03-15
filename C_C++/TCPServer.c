#include<sys/time.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 3333

int main()
{
	fd_set readfds, testfds;
	char sendbuf[32] = "thanks";
	char buf[256];
	int s_fd, c_fd;
	int s_len, c_len;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = PORT;
	s_len = sizeof(s_addr);
	printf("Host IP Address: %d\n", s_addr.sin_addr.s_addr);

	bind(s_fd, (struct sockaddr*)&s_addr, s_len);
	listen(s_fd, 10);
	FD_ZERO(&readfds);
	FD_SET(s_fd, &readfds);
	while(1)
	{
		/*
		printf("please wait a moment!\n");
		c_len = sizeof(c_addr);
		c_fd = accept(s_fd, (struct sockaddr*)&c_addr, (socklen_t *__restrict)&c_len);
		recv(c_fd, buf, 256, 0);
		buf[sizeof(buf)-1] = '\0';
		printf("buf size: %ld\n", sizeof(buf));
		printf("receive message:\n %s\n", buf);
		send(c_fd, sendbuf, sizeof(sendbuf), 0);
		close(c_fd);
		*/

		int fd;
		int nread;
		int result;
		testfds = readfds;
		printf("server is waiting!\n");

		result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);

		for(fd=0; fd<FD_SETSIZE; fd++)
		{
			if(FD_ISSET(fd, &testfds))
			{
				if(fd == s_fd)
				{
					c_len = sizeof(c_addr);
					c_fd = accept(s_fd, (struct sockaddr*)&c_addr, (socklen_t *__restrict)&c_len);
					FD_SET(c_fd, &testfds);
					printf("adding a client: %d\n", fd);
				}
				else
				{
					ioctl(fd, FIONREAD, &nread);

					if(nread == 0)
					{
						close(fd);
						FD_CLR(fd, &testfds);
						printf("removing a client: %d\n", fd);
					}
					else
					{
						read(fd, buf, sizeof(buf));
						sleep(5);
						printf("serving on fd: %d, get msg: %s\n", fd, buf);
						write(fd, sendbuf, sizeof(sendbuf));
					}
				}
			}
		}
	}
}

