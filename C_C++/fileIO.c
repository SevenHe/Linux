#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
	char *path = "/home/seven/Code/records.log";
	int fd;
	char buf[40], buf2[] = "hello mrcft";
	int n, i;
	if((fd = open(path, O_RDWR)) < 0)
	{
		perror("open file failed!");
		return 1;
	}
	else
		printf("open file successfully!\n");
	if((i = lseek(fd, 11, SEEK_SET)) < 0)
	{
		perror("lseek error!\n");
		return 1;
	}
	else
	{
		if(write(fd, buf2, 11) < 0)
		{
			perror("write error!\n");
			return 1;
		}
		else
		{
			printf("write successfully!\n");
		}
	}
	close(fd);					/* save the file when closing the file */
	
	if((fd = open(path, O_RDWR)) < 0)
	{
		perror("open file failed!\n");
		return 1;
	}
	if((n = read(fd, buf, 40)) < 0)
	{
		perror("read 2 failed!\n");
		return 1;
	}
	else
	{
		printf("read the changed data!\n");
		printf("data: %s\n", buf);
	}
	if(close(fd) < 0)
	{
		perror("close failed!\n");
		return 1;
	}
	else
		printf("Good bye!\n");

	return 0;
}


