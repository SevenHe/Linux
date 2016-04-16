#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define bool int 
#define false 0
#define true 1

int main()
{
	int n = 0;
	scanf("%d", &n);
	char** input = (char**)malloc(sizeof(char*)*n);
	float* result = (float*)malloc(sizeof(float)*n);
	float mass[4] = {12.01, 1.008, 16.00, 14.01};
	for(int i=0; i<n; i++)
	{
		result[i] = 0;
		input[i] = (char*)malloc(sizeof(char)*80);
		scanf("%s", input[i]);
		int len = strlen(input[i]);
		char temp = '\0';
		int count = 0;
		for(int t=0; t<len; t++)
		{
			if(temp == '\0')
			{
				temp = input[i][t];
			}
			else if(input[i][t] >= '0' && input[i][t] <= '9')
			{
				if(count != 0)
				{
					count *= 10;
					count += (int)(input[i][t] - '0');
				}
				else
					count += (int)(input[i][t] - '0');
			}
			bool is_calculatable = false;
			if(input[i][t] >= 'A' && input[i][t] <= 'Z' && t != 0)
			{
				is_calculatable = true;
			}
			if(is_calculatable)
			{
				if(count == 0)
				{
					count = 1;
				}
				switch(temp)
				{
					case 'C':
						result[i] += count*mass[0];
						break;
					case 'H':
						result[i] += count*mass[1];
						break;
					case 'O':
						result[i] += count*mass[2];
						break;
					case 'N':
						result[i] += count*mass[3];
						break;
				}
				temp = input[i][t];
				count = 0;
				continue;
			}
		}
		count = count == 0 ? 1 : count;
		// do some stupid jobs
		switch(temp)
		{
			case 'C':
				result[i] += count*mass[0];
				break;
			case 'H':
				result[i] += count*mass[1];
				break;
			case 'O':
				result[i] += count*mass[2];
				break;
			case 'N':
				result[i] += count*mass[3];
				break;
		}
	}
	for(int i=0; i<n; i++)
	{
		free(input[i]);
		printf("%.3f\n", result[i]);
	}
	free(input);
	free(result);
}

