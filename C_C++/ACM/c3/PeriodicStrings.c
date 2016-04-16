#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _bool int
#define true 1
#define false 0

int main()
{
	int n;
	char blank_line[80];
	scanf("%d", &n);
	char* input = (char*)malloc(sizeof(char)*80);
	int* result = (int*)calloc(n, sizeof(int));
	for(int i=0; i<n; i++)
	{
		fgets(blank_line, sizeof(blank_line), stdin);
		scanf("%s", input);
		int len = strlen(input);
		int min = len;
		_bool isCompleted = false;
		// can be speeded up simply
		// just iterate the input, and if there is no character equal to the input[0]
		// just no repeat, complexity O(n)
		if(len & 1)
		{
			for(int j=0; j<len/2 && !isCompleted; j+=2)
			{
				int start = 0;
				for(int k=j+1; k<len; k++)
				{
					if(input[k] != input[start % (j+1)])
						break;
					else if(input[k] == input[start % (j+1)])
					{
						start ++;
						if(k == len - 1)
						{
							min = j+1;
							isCompleted = true;
						}
					}
				}
			}
		}
		else
		{
			for(int j=0; j<len/2 && !isCompleted; j++)
			{
				if(len % (j+1) != 0)
					continue;
				int start = 0;
				for(int k=j+1; k<len; k++)
				{
					if(input[k] != input[start % (j+1)])
						break;
					else if(input[k] == input[start % (j+1)])
					{
						start ++;
						if(k == len - 1)
						{
							min = j+1;
							isCompleted = true;
						}
					}
				}
			}
		}
		result[i] = min;


		/* This method is too logical to write it completely
		char temp[80] = "";
		int index = 0;
		int adding = 0;
		int min = len;
		int record_first_letter = 0;
		FLAG flag = _INIT();
		
		for(int j=0; j<len; j++)
		{
			if(j == 0)
			{
				temp[adding] = input[j];
				adding++;
			}
			else if(temp[index] != input[j])
			{
				temp[adding] = input[j];
				adding++;
				printf("dismatch: temp %c, input %c\n", temp[index], input[j]);
				if(flag & _JUDGE && index <= result[i]-1)
				{
					printf("a failure match at: %c, input[%d]\n", temp[index], j);
					result[i] = record_first_letter == 0 ? j : record_first_letter;
					flag = (flag ^ _RESET) >> 1;
					index = 0;
				}
			}
			else if(temp[index] == input[j])
			{
				if(!(flag & _JUDGE))
				{
					printf("get into a judgement, result: %d\n", result[i]);
					if(result[i] == 0) result[i] = adding;
					flag |= _JUDGE;
				}
				else
				{
					if(input[j] == temp[0])
						record_first_letter = record_first_letter == 0 ? j : record_first_letter;
				}
				if(flag & _JUDGE && index == result[i]-1)
				{
					printf("complete a judgement, final comparator: %c, %c\n", temp[index], input[j]);
					if(j == len -1)
						min = result[i];
					flag = (flag ^ _RESET) >> 1;
					index = 0;
				}
				index ++;
				printf("match: temp %c, input %c\n", temp[index-1], input[j]);
				temp[adding] = input[j];
				adding ++;
			}
		}
		result[i] = min;
		*/
	}

	for(int i=0; i<n; i++)
	{
		if(i != 0)
			printf("\n");
		printf("%d\n", result[i]);
	}
	free(result);
	free(input);
}

		
