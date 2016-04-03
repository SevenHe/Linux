#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO "/home/seven/Code/C_C++/fifo-mk"

//BUFSIZ is defined in the stdlib.h, it is a part of system config.
int main(void)
{
	int fd;
	int pid;
	char r_msg[BUFSIZ];
	if((pid=mkfifo(FIFO, 0777)) == -1)
	{
		perror("create fifo channel failed");
		return 1;
	}
	else
		printf("create successfully!\n");
	fd = open(FIFO, O_RDWR);
	if(fd == -1)
	{
		printf("cannot open the FIFO.\n");
		return 1;
	}
	if(write(fd, "hello world", 12) == -1)
	{
		printf("write data error!\n");
		return 1;
	}
	else
		printf("write data successfully!\n");
	if(read(fd, r_msg, BUFSIZ) == -1)
	{
		printf("read error!\n");
		return 1;
	}
	else 
		printf("the receive data is %s !\n", r_msg);
	close(fd);
	return 0;
}
