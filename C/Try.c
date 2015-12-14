#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
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

	return 0;
}
