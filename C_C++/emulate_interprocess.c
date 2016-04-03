/*
	the implementation is based in buffering, and emulate/simulate 
	the communication processes in Linux System about receiving and sending message.
	group:54130714, 19, 20.
	Issue:7.
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "seven_df.h"

typedef struct chain {
	int usage;
	char buf[MESSAGE_SIZE];                 //char[] buf; java syntax!
	char* next;
}chain;

/* this idea can be better to use class syntax and extend relation. */
/* the identifier is for the privilege development, in the future*/
struct send {
	int index;
	//int identifier;
	char* smsg;
	pthread_t p_send;
};
struct receive {
	int index;
	//int identifier;
	char* rmsg;
	pthread_t p_receive;
};

chain* messages;	
struct send sends[MAXSEND_T];
struct receive receives[MAXRECEIVE_T];
pthread_mutex_t send_wait, receive_wait;
pthread_mutex_t main_wait;
int demo_time = 10;
int MESSAGE_C_SIZE = 0;

/* char is only accommodate a character, char* can get a string. */
/* In the beginning, I simulate the message as "None" for the pure string(initialization), and as other strings for use.
   but a best way is to initialize the char array assigned to ""(empty) or add a parameter for indicating the buf string is in use or not!
   -------have improved!*/
int main()
{	
	pthread_mutex_lock(&main_wait);
	int i;
	printf("Please input the capability:");
	scanf("%d", &MESSAGE_C_SIZE);
	messages = (chain*)malloc(sizeof(chain)*MESSAGE_C_SIZE);
	
	initialize();
	
	for(i=0; i<MESSAGE_C_SIZE; i++)
	{
		char input[MESSAGE_SIZE];
		printf("Please input the test message %d:", i);
		scanf("%s", input);
		if(strlen(input) <= MESSAGE_SIZE)
		{
			strcpy(messages[i].buf, input);
			messages[i].usage = MESSAGE_SIZE - strlen(input);
		}
	}
	showBlocks();
	printf("\n\n\n");
	// must consider the order of initializing!
	pthread_mutex_lock(&send_wait);
	for(i=0; i<MAXSEND_T; i++)
	{
		// more than one arg, you can use a struct to pass
		pthread_create(&sends[i].p_send, NULL, (void*)send_msg, &sends[i].index);
	}
	pthread_mutex_lock(&receive_wait);
	for(i=0; i<MAXRECEIVE_T; i++)
	{
		pthread_create(&receives[i].p_receive, NULL, (void*)receive_msg, &receives[i].index);
	}
	// put a seed.
	srand((unsigned)time(NULL));
	for(i=0; i<demo_time; i++)
	{
		printf("\n\n");
		system("date");
		//random pick
		int j = rand() % 10;
		if(j >= 5 && j < 10)
		{	
			pthread_mutex_unlock(&receive_wait);
			pthread_mutex_lock(&main_wait);
			//if you want to use the thread recursively, you must relock it in the built-in method.
		}
		else if(j >= 0 && j < 5)
		{	
			pthread_mutex_unlock(&send_wait);
			pthread_mutex_lock(&main_wait);
		}
		else
		{
			printf("the selected index is %d, invalid!", j);
			exit(EXIT_FAILURE);
		}
		sleep(5);
	}
	free(messages);
	exit(EXIT_SUCCESS);
		
	/*FOR TEST
	another way, easy but not so concrete.
	scanf("MESSAGE_SIZE%s", messages[0].buf);  
	printf("Text:%s \n", messages[0].buf);
	exit(EXIT_SUCCESS);
	*/
};

void initialize()
{	
	int i;
	for(i=0; i<MESSAGE_C_SIZE; i++)
	{
		strcpy(messages[i].buf, "");
		messages[i].usage = MESSAGE_SIZE;
		if(i != MESSAGE_C_SIZE - 1)
			messages[i].next = messages[i+1].buf;
		else
			messages[i].next = NULL;
	}
	
	pthread_mutex_init(&main_wait, NULL);
	for(i=0; i<MAXSEND_T; i++)
	{
		sends[i].index = i;
		//Initialize!
		char smsgBuf[MESSAGE_SIZE];
		sends[i].smsg = smsgBuf; 
		//sends[i].identifier = SEND_PRIVILEGE;
	}
	pthread_mutex_init(&send_wait, NULL);
	for(i=0; i<MAXRECEIVE_T; i++)
	{
		receives[i].index = i;
		char rmsgBuf[MESSAGE_SIZE];
		receives[i].rmsg = rmsgBuf;
		//receives[i].identifier = RECEIVE_PRIVILEGE;
	}
	pthread_mutex_init(&receive_wait, NULL);
	
};

void send_msg(int* index)
{
	while(*index <= MAXSEND_T)
	{	
		//though release the lock, it still run continuously, manually eject the logic.
		pthread_mutex_lock(&send_wait);
		int k;
		printf("********************************\n");
		for(k=0; k<MESSAGE_C_SIZE; k++)
			if(messages[k].next == NULL)
			{	
				int t;
				if(!strcmp(messages[k].buf, ""))
					t = k;
				else
					t = k + 1;
				if(t < MESSAGE_C_SIZE)
				{
					sprintf(messages[t].buf, "send %d message", *index);
					messages[k].next = messages[t].buf;
					messages[t].next = NULL;	
					printf("Send Process %d send %d message. \n", *index, *index);
					break;
				}
				else
				{
					printf("There is not space for Send Process %d to add message! \n", *index);
					break;
				}
			}
		printf("********************************\n");
		showBlocks();
		pthread_mutex_unlock(&main_wait);
	}
		
};

void receive_msg(int* index)
{
	while(*index <= MAXRECEIVE_T)
	{
		pthread_mutex_lock(&receive_wait);
		int k;
		printf("********************************\n");
		for(k=0; k<MESSAGE_C_SIZE; k++)
			if(messages[k].next == NULL)
			{
				if(strcmp(messages[k].buf, ""))
				{
					strcpy(receives[*index].rmsg, messages[k].buf);
					strcpy(messages[k].buf, "");
					if(k-1 >= 0) messages[k-1].next = NULL;
					printf("Receive Process %d  get %s. \n", *index, receives[*index].rmsg);
					break;
				}
				else
				{	
					printf("Though the buf is empty, the order 'receive' of calling is wrong! \n");
					break;
				}
			}
		printf("********************************\n");
		showBlocks();
		pthread_mutex_unlock(&main_wait);
	}
};
	
void showBlocks()
{	
	printf("===============================\n");
	int k;
	for(k=0; k<MESSAGE_C_SIZE; k++)
		printf("Message %d: %s \n", k, messages[k].buf);
	printf("===============================\n");
};
		

	
