#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int n;
	scanf("%d", &n);
	char* input = (char*)malloc(sizeof(char)*10000);
	int result[20][10];
	memset(result, 0, sizeof(result));
	for(int i=0; i<n; i++)
	{
		scanf("%s", input);
		int len = strlen(input);
		for(int j=0; j<len; j++)
		{
			result[i][input[j] - '0'] ++;
		}
		memset(input, 0, sizeof(char)*len);
	}
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<10; j++)
		{
			if(j == 9)
				printf("%d\n", result[i][j]);
			else
				printf("%d ", result[i][j]);
		}
	}
	free(input);
}

		
