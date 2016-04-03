#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

extern char **environ;

void exit_s(int status)
{
	if(WIFEXITED(status))
		printf("normal exit, status=%d\n", WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("signal exit! status=%d\n", WTERMSIG(status));
}

int main(int argc, char* argv[])
{
	/* some exec kind methods tests
	pid_t pid;
	if((pid=fork())<0)
		puts("create child process failed!");
	if(pid == 0)
		execve("Try", argv, environ);
	//execlp("/bin/vim", "vim", "file path....", (char*)NULL);
	else
		puts("This message is printed out when successful!");
	*/

	pid_t pid, pid1;
	int status;
	if((pid=fork())<0)
	{
		printf("child process error!\n");
		exit(0);
	}
	else if(pid == 0)
	{
		// get into the child process
		printf("the child process!\n");
		exit(2);
	}
	// wait the child process to exit, and return the child pid
	if(wait(&status) != pid)
	{
		printf("this is a parent process!\nwait error!\n");
		exit(0);
	}
	exit_s(status);
	if((pid=fork())<0)
	{
		printf("child process error!\n");
		exit(0);
	}
	else if(pid == 0)
	{
		printf("the child process!\n");
		pid1 = getpid();
	// 	kill(pid1, 9);				/* finish the process */
	// 	kill(pid1, 17);				/* get into the parent process */
		kill(pid1, 19);				/* stop the process */
	}
	if(wait(&status) != pid)
	{
		printf("this is a parent process!\nwait error!\n");
		exit(0);
	}
	exit_s(status);


	return 0;
}
