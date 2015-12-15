#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	/* file tests!
	FILE *f;
	char msg[] = "456 I am ok 123";
	// do some initialization to avoid the interference of the pointer.
	char rcv[20] = "";
	f = fopen("./test.txt", "w+");
	fwrite(msg, strlen(msg), 1, f);
	fclose(f);

	if((f = fopen("./test.txt", "r")) != NULL)
	{
		fprintf(stdout, "Opening is successful.\n");
		//fread(rcv, 1, strlen(msg), f);
		while(!feof(f))
		{
			fscanf(f, "%s", msg);
			strcat(msg, " ");
			strcat(rcv, msg);	
			printf("get msg: %s\n", rcv);
		}
		printf("int: %d\n", atoi(rcv));
		fclose(f);
	}
	*/
	int a=5,b=3,c=0;
	// a>b get a return value that is 1 for true, 0 for false.(It is always true without zero!)
	if((a > b) > c)
	{
		printf("c=%d\n", c);
	}

	return 0;
}
