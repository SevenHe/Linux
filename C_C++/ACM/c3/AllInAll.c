#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _bool unsigned int
#define true 1
#define false 0

int main()
{
	char pattern[1023] = "";
	char src[1023] = "";
	while(scanf("%s %s", pattern, src) != EOF)
	{
		int p_len = strlen(pattern);
		int s_len = strlen(src);
		int p_index = 0;
		_bool found = false;
		for(int i=0; i<s_len; i++)
		{
			if(pattern[p_index] == src[i])
			{
				p_index ++;	
				if(p_index == p_len)
				{
					found = true;
					break;
				}
			}
		}
		if(found)
			printf("Yes\n");
		else
			printf("No\n");
	}
}
