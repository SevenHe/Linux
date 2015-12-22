#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define RESOURCE 4
/* you must take care of the msg that could be provided for you from man pages!!! */
union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};

int main(void)
{
	key_t key;
	int semid;
	struct sembuf sbuf = {0, -1, IPC_NOWAIT};
	// 0 means there is a number of '0' semaphore being operating, -1 is to acquire the semaphore, and IPC_NOWAIT is literal.
	union semun arg;
	if((key = ftok("/home/seven", 'c')) == -1)
	{
		perror("ftok error!\n");
		exit(1);
	}
	if((semid = semget(key, 1, IPC_CREAT|0666)) == -1)
	{
		perror("semget error!\n");
		exit(1);
	}
	arg.val = RESOURCE;
	printf("Available resources are %d in total!\n", arg.val);
	if(semctl(semid, 0, SETVAL, arg) == -1)
	{
		perror("semctl error!\n");
		exit(1);
	}
	while(1)
	{
		if(semop(semid, &sbuf, 1) == -1)
		{
			perror("semop error!\n");
			exit(1);
		}
		sleep(5);
	}
	semctl(semid, 0, IPC_RMID, 0);
	exit(0);
}	
