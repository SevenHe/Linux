/*
	Only record 2 days' situation,so it's concrete for now.
	
*/

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//Every two hours to record.
int time = 0;

void record()
{	
	if(time != 24) {
		system("sar -u >> records.log");
		printf("ok");
	}
	else
		system("sar -u > records.log");
	return;
}

int main()
{
	//Auto config daemon environment......---unuseful.
	//daemon(0, 0);
	
	pid_t pid;
  	if(pid=fork())
    	exit(0);
  	else if(pid< 0)
    	exit(1);

  	setsid();
  	if(pid=fork())
    	exit(0);
  	else if(pid< 0)
    	exit(1);

	int i;
	int size;
  	for(i=0,size=getdtablesize(); i<size; ++i)
    	close(i);
  	//chdir("/tmp");
  	//umask(0);
	
	signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP ,SIG_IGN);
    
	while(1)
	{	
		record();
		if(time == 24)
			time = 0;
		else
			time ++;
		sleep(3600*2);
	}
	
}
		