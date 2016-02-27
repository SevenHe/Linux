#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<arpa/inet.h>

#define PORT 8888

int main(int argc, char **argv)
{
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	int sock;
	socklen_t addr_len;
	int len;
	char buf[128];
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket!\n");
		exit(errno);
	}
	else
		printf("create socket successful!\n\r");
	memset(&s_addr, 0, sizeof(struct sockaddr_in));
	s_addr.sin_family = AF_INET;
	if(argv[2])
		s_addr.sin_port = htons(atoi(argv[2]));
	else
		s_addr.sin_port = htons(PORT);
	if(argv[1])
		s_addr.sin_addr.s_addr = inet_addr(argv[1]);
	else
		s_addr.sin_addr.s_addr = htons(INADDR_ANY);			/* set the host address */
	if((bind(sock, (struct sockaddr*)&s_addr, sizeof(s_addr))) == -1)
	{
		perror("bind error!\n");
		exit(errno);
	}
	else
		printf("bind address to socket successfully!--%d\n\r", s_addr.sin_addr.s_addr);
	addr_len = sizeof(c_addr);
	while(1)
	{
		len = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&c_addr, &addr_len);
		if(len < 0)
		{
			perror("recvfrom error!\n");
			exit(errno);
		}
		buf[len] = '\0';
		printf("receive from remote host %s, port %d, msg:\n %s\n\r", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port), buf);
	}

	return 0;
}
