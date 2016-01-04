#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

static void sig_handler(int signo)
{
	printf("signal SIGINT has been raised! \n");
}

int main()
{
	sigset_t new, old, pend;
	if(signal(SIGINT, sig_handler) == SIG_ERR)		/* register a signal handler function */
	{
		perror("signal!\n");
		exit(1);
	}
	if(sigemptyset(&new) < 0)						/* empty the signal set */
		perror("sigaddset!\n");
	if(sigaddset(&new, SIGINT) < 0)					/* add SIGINT signal to the 'new' set */
	   perror("sigaddset!\n");	
	if(sigprocmask(SIG_SETMASK, &new, &old) < 0)	/* block the new signal set to wait the signal */
	{
		perror("sigprocmask!\n");
		exit(1);
	}
	printf("SIGQUIT is blocked!\n");
   	printf("Try to Ctrl+C, program will suspend 5s to handler the event!\n");
   	sleep(5);
	if(sigpending(&pend) < 0)						/* get the pending signal type */
		perror("sigpending!\n");
	if(sigismember(&pend, SIGINT))					/* check SIGINT is a member of pending signal type */
		printf("signal SIGINT is pending.\n");
	if(sigprocmask(SIG_SETMASK, &old, NULL) < 0)	/* recover previous signal mask */
	{
		perror("sigprocmask!\n");
		exit(1);
	}
	printf("SIGINT has been unblocked!\n");
	printf("Another try to press Ctrl+C \n");
	sleep(5);
	return 0;
}
/* This program proves that if there is no sigpending(), every sleep() cannot be executed correctly,
 * that is if set sigpending() after sleep(), it will handle the event after specified seconds.
 * sigpending() is used after sigprocmask() which is to set the process blocked!
 */
