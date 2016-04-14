#include<stdio.h>
#include<string.h>
#define maxn 1000000

int main()
{
	char s[maxn];
	scanf("%s", s);
	int count = 0;
	int len = strlen(s);
	printf("len: %d\n", len);
	for(int i=0; i<len; i++)
		if(s[i] == '1')
			count ++;
	printf("count: %d\n", count);
	return 0;
}
