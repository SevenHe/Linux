#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main()
{
	int shmid;
	//int proj_id;
	key_t key;
	//int size;
	char *addr;
	pid_t pid;
	key = IPC_PRIVATE;
	shmid = shmget(key, 1024, IPC_CREAT|0660);
	if(shmid == -1)
	{
		perror("create share memory failed!\n");
		return 1;
	}
	addr = (char*)shmat(shmid, NULL, 0);
	char *test_addr = addr;
	if(addr == (char*)(-1))
	{
		perror("cannot attach!\n");
		return 1;
	}
	printf("share memory segment's address:%p\n", addr);
	strcpy(addr, "welcome to microsoft!");
	printf("test addr by access the 0x..: %c.\n", *(test_addr+1));
	pid = fork();
	if(pid == -1)
	{
		perror("error!!!!!\n");
		return 1;
	}
	else if(pid == 0)
	{
		printf("child process string is '%s'.\n", addr);
		strcat(addr, "--after child process");
		_exit(0);
	}
	else
	{
		wait(NULL);
		printf("parent process string is '%s'.\n", addr);
		if(shmdt(addr) == -1)
		{
			perror("release failed!\n");
			return 1;
		}
		if(shmctl(shmid, IPC_RMID, NULL) == -1)
		{
			perror("failed in the last!\n");
			return 1;
		}
	}

	return 0;
}
