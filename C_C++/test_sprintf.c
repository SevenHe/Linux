#include<stdio.h>

int main()
{
	char test[64] = "";
	char input[10] = "jlakdf";
	sprintf(test, "%s--1", input);
	printf("%s\n", test);
	sprintf(test, "%s--2", input);
	printf("%s\n", test);
	return 0;
}
