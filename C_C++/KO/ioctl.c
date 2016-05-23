#include "chardev.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

void ioctl_set_msg(int file_desc, char* msg)
{
	int ret;
	ret = ioctl(file_desc, IOCTL_SET_MSG, msg);
	if(ret < 0)
	{
		printf("ioctl_set_msg failed:%d\n", ret);
		exit(-1);
	}
}

void ioctl_get_msg(int file_desc)
{
	int ret;
	char msg[100];
	ret = ioctl(file_desc, IOCTL_GET_MSG, msg);
	if(ret < 0)
	{
		printf("ioctl_get_msg failed:%d\n", ret);
		exit(-1);
	}

	printf("get msg: %s\n", msg);
}

void ioctl_get_nth_byte(int file_desc)
{
	int i;
	char c;
	printf("get_nth_byte msg:");
	i = 0;
	while(c != 0)
	{
		c = ioctl(file_desc, IOCTL_GET_NTH_BYTE, i);
		i ++;

		if(c < 0)
		{
			printf("ioctl_get_nth_byte failed at %d'th byte:\n", i);
			exit(-1);
		}

		putchar(c);
	}
	putchar('\n');
}

int main()
{
	int file_desc, ret;
	char* msg = "Message passed by ioctl\n";
	file_desc = open(DEVICE_FILE_NAME, 0);
	if(file_desc < 0)
	{
		printf("cannot open the device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ioctl_get_nth_byte(file_desc);
	ioctl_get_msg(file_desc);
	ioctl_set_msg(file_desc, msg);

	close(file_desc);
	return 0;
}

