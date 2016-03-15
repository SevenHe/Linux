#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>					/* contain relative structs about AF_INET */
#include<arpa/inet.h>					/* contain relative functions about AF_INET */

#define PORT 3333

int main()
{
	int sockfd;
	int len;
	struct sockaddr_in addr;
	int state;
	char buf[32] = "come on!";
	int len2;
	char rebuf[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = PORT;
	len = sizeof(addr);
	state = connect(sockfd, (struct sockaddr*)&addr, len);
	if(state == -1)
	{
		perror("connection is failed!\n");
		return 1;
	}
	len2 = sizeof(buf);
	send(sockfd, buf, len2, 0);
	sleep(5);
	recv(sockfd, rebuf, 256, 0);
	rebuf[sizeof(rebuf)-1] = '\0';
	printf("receive message:\n %s\n", rebuf);
	close(sockfd);

	return 0;
}
