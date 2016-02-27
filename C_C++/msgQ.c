#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(void)
{
	key_t key;
	int proj_id = 1;
	int msqid;
	char message1[] = {"hello microsoft"};
	char message2[] = {"goodbye"};
	struct msgbuf			/* you need to define your own msgbufs */
	{
		long msgtype;
		char msgtext[1024];
	}snd, rcv;
	key = ftok("/home/seven", proj_id);
	if(key == -1)
	{
		perror("create key error!\n");
		return 1;
	}
	if((msqid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		printf("msgget error!\n");
		exit(1);
	}
	snd.msgtype = 1;
	//just like the fprintf, for catenation.
	sprintf(snd.msgtext, "%s", message1);
	// +1 is for the end character '\0'.
	if(msgsnd(msqid, (struct msgbuf*)&snd, sizeof(message1)+1, 0) == -1)
	{
		printf("msgsnd 1 error!\n");
		exit(1);
	}
	snd.msgtype = 2;
	sprintf(snd.msgtext, "%s", message2);
	if(msgsnd(msqid, (struct msgbuf*)&snd, sizeof(message2)+1, 0) == -1)
	{
		printf("msgsnd 2 error!\n");
		exit(1);
	}
	if(msgrcv(msqid, (struct msgbuf*)&rcv, 80, 1, IPC_NOWAIT) == -1)
	{
		printf("msgrcv 1 error!\n");
		exit(1);
	}
	printf("the received message1: %s.\n", rcv.msgtext);
	if(msgrcv(msqid, (struct msgbuf*)&rcv, 80, 2, IPC_NOWAIT) == -1)
	{
		printf("msgrcv 2 error!\n");
		exit(1);
	}
	printf("the received message2: %s.\n", rcv.msgtext);
	/* if you do not have caches in the msg queue, there will be not bytes after all msgs being received. */
	system("ipcs -q");
	msgctl(msqid, IPC_RMID, 0);		// delete the msg queue.
	system("ipcs -q");
	exit(0);
}

