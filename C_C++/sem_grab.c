#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

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
	int semid, semval;
	//union semun arg; // for semctl!
	/* the pathname could be a user's path to identified by others*/
	if((key = ftok("/home/seven", 'c')) == -1)		
	{
		perror("key error!\n");
		exit(1);
	}
	if((semid = semget(key, 1, IPC_CREAT|0666)) == -1)
	{
		perror("semget error!\n");
		exit(1);
	}
	while(1)
	{
		if((semval = semctl(semid, 0, GETVAL, 0)) == -1)
		{
			perror("semctl error!\n");
			exit(1);
		}
		if(semval > 0)
		{
			printf("There are %d resource(s) that can be used!\n", semval);
		}
		else
		{
			printf("There is no another resource!\n");
			break;
		}
		sleep(3);
	}
	exit(0);
}
