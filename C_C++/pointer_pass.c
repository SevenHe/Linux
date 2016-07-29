#include <stdio.h>
#include <stdlib.h>

/* so, pass the '&' address, and in the function, do the * to get the real var.
 * and, we can change it.
 */

void swap1(char** s1, char** s2)
{
	char** tmp = s1;
	s1 = s2;
	s2 = tmp;
}

void swap2(char* ss1, char* ss2)
{
	char* tmp = ss2;
	ss1 = ss2;
	ss2 = tmp;
}

char* testc()
{
	char* tmp = (char*)malloc(sizeof(char)*20);
	tmp[0] = 'i';
	tmp[1] = 'a';
	tmp[2] = 'm';
	tmp[3] = 'o';
	tmp[4] = 'k'; 
	return tmp;
}

int main()
{
	char* t1 = "iamok!";
	char* t2 = "okmai!";
	char** a = &t1;
	printf("%s, %s\n", t1, t2);
	swap1(a, &t2);
	printf("%s, %s\n", t1, t2);
	int arr[10];
	int *p = arr;
	printf("p:%p, %p\n", p, p+1);
	// p = &arr; will raise a warning! int *a[10] <=> int *a;
	p = &(arr[0]);
	printf("p:%p, %p\n", p, p+1);
	char* t3 = testc();
	printf("t3:%s\n", t3);
	free(t3);
}
