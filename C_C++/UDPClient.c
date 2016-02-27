#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<stdlib.h>
#include<arpa/inet.h>

#define PORT 8888									/* the server port */

int main(int argc, char **argv)
{
	struct sockaddr_in s_addr;
	int sock;
	int addr_len;
	int len;
	char buf[] = "Hello everyone, Merry Christmas!";
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket error!\n");
		exit(errno);
	}
	else
		printf("create socke successfully!\n");
	s_addr.sin_family = AF_INET;
	if(argv[2])
		s_addr.sin_port = htons(atoi(argv[2]));
	else
		s_addr.sin_port = htons(PORT);					/* must be converted!! */
	if(argv[1])
		s_addr.sin_addr.s_addr = inet_addr(argv[1]);
	else
	{
		printf("Have not input the receiver!\n");
		//wrong - - s_addr.sin_addr.s_addr = INADDR_ANY;
		exit(0);
	}
	addr_len = sizeof(s_addr);
	len = sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&s_addr, addr_len);
	if(len < 0)
	{
		printf("\n\rsend error!\n\r");
		return 3;
	}
	printf("send successfully!\n\r");
	
	return 0;
}

