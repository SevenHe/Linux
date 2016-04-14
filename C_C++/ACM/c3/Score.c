#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct test {
	const int b;
};

int main()
{
	int lines = 0;
	scanf("%d", &lines);
	char** input = (char**)malloc(sizeof(char*)*lines);
	int* score = (int*)malloc(sizeof(int)*lines);
	memset(score, 0, sizeof(int)*lines);
	for(int i=0; i<lines; i++)
	{
		input[i] = (char*)malloc(sizeof(char)*80);
		scanf("%s", input[i]);
		int len = strlen(input[i]);
		int temp = 0;
		for(int j=0; j<len; j++)
		{
			if(temp == 0 && input[i][j] == 'O')
			{
				temp = 1;
				score[i] += temp;
			}
			else if(temp != 0 && input[i][j] == 'O')
			{
				temp ++;
				score[i] += temp;
			}
			else if(temp != 0 && input[i][j] == 'X')
			{
				temp = 0;
				score[i] += temp;
			}
			else
				continue;
		}
	}
	for(int i=0; i<lines; i++)
	{
		printf("%d\n", score[i]);
		free(input[i]);
	}
	free(score);
	free(input);

	return 0;
}

