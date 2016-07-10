#include <stdio.h>

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

int main()
{
	char* t1 = "iamok!";
	char* t2 = "okmai!";
	char** a = &t1;
	printf("%s, %s\n", t1, t2);
	swap1(a, &t2);
	printf("%s, %s\n", t1, t2);
}
