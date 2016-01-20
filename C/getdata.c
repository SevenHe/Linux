#include <stdio.h>
#include "getdata.h"

void getdata(int *n, int *k)
{
	char prompt[100];
	sprintf(prompt, "Please input the sum of samples(<%d) ", FACMAX);
	*n = input(prompt);
	do{
		sprintf(prompt, "\nPlease input the samples that will be used(<%d>=%d) ", FACMAX, *n);
		*k = input(prompt);
	}while(n<k);
}

int input(char *prompt)
{
	int x;
	do{
		puts(prompt);
		scanf("%d", &x);
	}while(x<=0 || x>FACMAX);
	
	return x;
}
