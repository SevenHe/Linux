#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp;
	char ch, filename[50];
	printf("please input file path and name:\n");
	scanf("%s", filename);
	if((fp = fopen(filename, "r")) == NULL)
	{
		printf("cannot open the file!\n");
		exit(0);
	}
	printf("len0=%ld\n", ftell(fp));
	ch = fgetc(fp);
	while(ch != EOF)
	{
		putchar(ch);
		ch = fgetc(fp);
	}
	printf("\n");
	printf("len1=%ld\n", ftell(fp));
	rewind(fp);
	printf("len2=%ld\n", ftell(fp));
	ch = fgetc(fp);
	while(ch != EOF)
	{
		putchar(ch);				/* just like the getchar(), to control stdin/out */
		ch = fgetc(fp);

	}
	printf("\n");
	fclose(fp);

	return 0;
}
