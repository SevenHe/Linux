#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	const char traits[4] = {'A', 'C', 'G', 'T'};
	int n;
	scanf("%d", &n);
	char** result = (char**)malloc(sizeof(char*)*n);
	// final Hamming value
	int* count = (int*)calloc(n, sizeof(int));
	// every position, A,T,C,G weights
	int weight[1000][4];
	for(int i=0; i<n; i++)
	{
		memset(weight, 0, sizeof(weight));
		int row;
		int column;
		scanf("%d %d", &row, &column);
		result[i] = (char*)malloc(sizeof(char)*column);
		char input[1000];
		//printf("row:%d, column:%d\n", row, column);
		if(row > 50) row = 50;
		for(int j=0; j<row; j++)
		{
			memset(input, 0, sizeof(input));
			scanf("%s", input);
			getchar();
			//printf("get a row: %s\n", input);
			for(int k=0; k<column; k++)
			{
				switch(input[k])
				{
					case 'A':
						weight[k][0] ++;
						break;
					case 'C':
						weight[k][1] ++;
						break;
					case 'G':
						weight[k][2] ++;
						break;
					case 'T':
						weight[k][3] ++;
						break;
				}
			}
		}
		// producing a result
		for(int j=0; j<column; j++)
		{
			int max_index = 0;
			for(int k=1; k<4; k++)
			{
				if(weight[j][k] > weight[j][max_index])
					max_index = k;
			}
			for(int k=0; k<4; k++)
			{
				if(k != max_index)
					count[i] += weight[j][k];
			}
			result[i][j] = traits[max_index];
		}
	}
	for(int i=0; i<n; i++)
	{
		printf("%s\n", result[i]);
		printf("%d\n", count[i]);
		free(result[i]);
	}
	free(result);
	free(count);
	return 0;
}




