#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int i = 0;

void new_handler(int sig)
{
	printf("receive signal number is: %d\n", sig);
	for(; i<100; i++)
	{
		printf("sleep2  %d\n", i);
		sleep(1);
	}
}

int main(void)
{
	struct sigaction newact, oldact;
	newact.sa_handler = new_handler;
	sigaddset(&newact.sa_mask, SIGQUIT);
	newact.sa_flags = SA_RESETHAND | SA_NODEFER;
	printf("change SIGINT(2) signal__[ctrl+c]\n");
	sigaction(SIGINT, &newact, &oldact);
	while(1)
	{
		sleep(1);
		printf("sleep1  %d\n", i);
		i++;
	}
	return 0;
}

