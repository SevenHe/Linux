#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _bool unsigned short
#define true 1
#define false 0

int main()
{
	int n;
	int m;
	int count = 1;
	int square_row[10][10];
	int square_column[10][10];
	while(scanf("%d", &n) != EOF)
	{
		//int** square_row = (int**)calloc(n+1, sizeof(int)*(n+1));
		//int** square_column = (int**)calloc(n+1, sizeof(int)*(n+1));
		memset(square_row, 0, sizeof(square_row));
		memset(square_column, 0, sizeof(square_column));

		// get m lines
		scanf("%d", &m);
		for(int i=0; i<m; i++)
		{
			getchar();
			char type = getchar();
			int j;
			int k;
			scanf("%d", &j);
			scanf("%d", &k);
			//printf("get %c %d %d\n", type, j, k);
			if(type == 'H')
				square_row[j][k] = 1;
			else
				square_column[j][k] = 1;
		}
		/*
		// test, print square
		for(int i=1; i<n+1; i++)
		{
			for(int j=1; j<n+1; j++)
			{
				if(square_row[i][j] == 1)
					printf("0 -- ");
				else
					printf("0    ");
			}
			printf("\n");
			for(int j=1; j<n+1; j++)
			{
				if(square_column[j][i] == 1)
					printf("|    ");
				else
					printf("     ");
			}
			printf("\n");
		}
		*/
		/*
		// judge square of size 1
		for(int i=1; i<n+1; i++)
		{
			if(i+1 > n)
				break;
			for(int j=1; j<n+1; j++)
			{
				if(j+1 > n)
					break;
				if(square_row[i][j] == 1 && square_row[i+1][j] == 1 &&
					square_column[j][i] == 1 && square_column[j+1][i])
					square[i][j] = 1;
			}
		}
		*/
		if(count > 1)
			printf("\n**********************************\n\n");
		printf("Problem #%d\n\n", count);
		count ++;
		_bool find_an_ans = false;
		for(int i=1; i<n+1; i++)
		{
			//printf("start size %d\n", i);
			int num = 0;
			for(int row=1; row<n+1; row++)
			{
				//printf("judge row: %d\n", row);
				if(row+i > n)
					break;
				for(int pos=1; pos<n+1; pos++)
				{
					//printf("judge start pos: %d\n", pos);
					//printf("row, pos value: %d\n", square_row[row][pos]);
					// pos - 1 + i > n - 1
					if(pos+i > n)
						break;
					else if(square_row[row][pos] != 1 || square_column[pos][row] != 1)
						continue;
					_bool is_ans = true;
					// judge horizontally
					for(int t=pos; t<pos+i; t++)
					{
						if(square_row[row][t] != 1 || square_row[row+i][t] != 1)
						{
							is_ans = false;
							//printf("H %d %d break!\n", square_row[row][t] == 1 ? row+i : row, t);
							break;
						}
						/*
						else
						{
							printf("H %d/%d %d passed!\n", row, row+i, t);
						}
						*/
					}
					// judge vertically
					for(int t=row; t<row+i&&is_ans; t++)
					{
						if(square_column[pos][t] != 1 || square_column[pos+i][t] != 1)
						{
							is_ans = false;
							//printf("V %d %d break!\n", square_column[pos][t] == 1 ? pos+i : pos, t);
							break;
						}
						/*
						else
						{
							printf("V %d/%d %d passed!\n", pos, pos+i, t);
						}
						*/
					}
					// is an answer?
					if(is_ans)
					{
						num ++;
						find_an_ans = true;
					}
				}
			}
			if(num != 0)
				printf("%d square (s) of size %d\n", num, i);
		}
		// get the solution
		if(!find_an_ans)
			printf("No completed squares can be found.\n");
	}

	return 0;
}
