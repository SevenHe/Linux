#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int i = 0;
	
	char** a = (char**)malloc(sizeof(char*)*600);
	for( ; i<600; i++)
	{
		a[i] = (char*)malloc(sizeof(char)*600);
		strcpy(a[i], "i am testing");
		printf("get a string: %s\n", a[i]);
	}
	/*
	char a[600][600];
	for(i=0; i<600; i++)
	{
		strcpy(a[i], "ima testlka\0");
		printf("get a string: %s\n", a[i]);
	}*/
	for(i=0; i<600; i++)
		free(a[i]);
	free(a);

	return 0;
}
