#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HEIGHT 3

// kmp is not suitable for this, because 1 can fit with 1 and 2.
// kmp does very good jobs for string by a next array, regression search!
// next[i] reflects the situation of i-1 chars.
int kick_down(char a[], char b[])
{
	int a_len = strlen(a);
	int b_len = strlen(b);
	int match = 0;
	int b_count = -1;
	for(int i=0; i<b_len; i++)
	{
		if(match == a_len) break;
		int temp_a = a[match] - '0';
		int temp_b = b[i] - '0';
		//printf("cmp: %d and %d\n", temp_a, temp_b);
		if(temp_a + temp_b <= HEIGHT)
			match ++;
		else
		{
			match = 0;
			b_count ++; 
			i = b_count;
		}
	}

	/* just a test */ 
	/*
	int* next = (int*)calloc(a_len+1, sizeof(int));
	// for next array
	int match_a = 0;
	// for match
	int match_b = 0;
	for(int i=0; i<b_len; i++)
	{
		int temp_a = a[match_b] - (int)'0';
		int temp_b = b[i] - (int)'0';
		if(temp_a + temp_b <= HEIGHT)
		{
			if(match_b == 0)
			{
				next[match_a] = 0;
			}
			else
			{	
				if(a[match_a] == a[match_b])
				{
					match_a ++;
					next[match_b] = next[match_b-1] + 1;
				}
				else

		else
		{
			
		}

	}
	free(next);
	*/
	return a_len + b_len - match;
}


int main()
{
	char a[101];
	char b[101];
	while(scanf("%s", a) != EOF)
	{
		scanf("%s", b);
		int a_len = strlen(a);
		int b_len = strlen(b);
		int result = 0;
		if(a_len >= b_len)
			result = kick_down(b, a);
		else
			result = kick_down(a, b);
		printf("%d\n", result);
		memset(a, '\0', sizeof(a));
		memset(b, '\0', sizeof(b));
	}
}

