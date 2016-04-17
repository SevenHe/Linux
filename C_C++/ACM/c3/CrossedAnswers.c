#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _bool int
#define true 1
#define false 0

int main()
{
	int row;
	int column;
	int puzzle_seq = 1;
	/*
	 * i use realloc originally, but for passing the test, use array to be simple
	 */
	int numbering[10][10];
	char puzzle[10][10];
	int last_row = 0;
	/* 
	 * realloc will not help to initialize the added memory, so it can be a value you do not need
	 * do it yourself!
	 */
	while(scanf("%d", &row) && row != 0)
	{
		if(row == 0)
			break;
		scanf("%d", &column);
		getchar();
		memset(numbering, 0, sizeof(numbering));
		memset(puzzle, 0, sizeof(puzzle));
		/*
		numbering = (int**)realloc(numbering, sizeof(int*)*row);
		puzzle = (char**)realloc(puzzle, sizeof(char*)*row);
		*/
		for(int i=0; i<row; i++)
		{
			/*
			numbering[i] = (int*)realloc(numbering[i], sizeof(int)*column);
			puzzle[i] = (char*)realloc(puzzle[i], sizeof(char)*column);
			*/
			scanf("%s", puzzle[i]);
			//printf("get a row: %s\n", puzzle[i]);
			getchar();	// for enter \n	
		}
		if(last_row != 0)
			printf("\n");
		last_row = row;
		int count = 1;
		// numbering
		for(int i=0; i<row; i++)
			for(int j=0; j<column; j++)
			{
				if(puzzle[i][j] == '*')
				{
					numbering[i][j] = -1;
				}
				else if((i == 0 || j == 0) && puzzle[i][j] != '*')
				{
					numbering[i][j] = count;
					count ++;
				}
				else if(i-1 >=0 && j-1 >= 0 && (puzzle[i-1][j] == '*' || puzzle[i][j-1] == '*'))
				{
					numbering[i][j] = count;
					count ++;
				}
				else
					numbering[i][j] = 0;
			}
		printf("puzzle #%d:\n", puzzle_seq);
		puzzle_seq ++;
		printf("Across\n");
		_bool in_printing = false;
		for(int i=0; i<row; i++)
		{
			in_printing = false;
			for(int j=0; j<column; j++)
			{
				if(numbering[i][j] >= 0)
				{
					if(numbering[i][j] >= 10 && !in_printing)
					{
						in_printing = true;
						printf(" %d.%c", numbering[i][j], puzzle[i][j]);
						if(j == column - 1)
							printf("\n");
					}
					else if(!in_printing)
					{
						in_printing = true;
						printf("  %d.%c", numbering[i][j], puzzle[i][j]);
						if(j == column - 1)
							printf("\n");
					}
					else if(in_printing)
					{
						printf("%c", puzzle[i][j]);
						if(j == column - 1)
						{
							in_printing = false;
							printf("\n");
						}
					}
				}
				else if(puzzle[i][j] == '*' && in_printing)
				{
					printf("\n");
					in_printing = false;
				}
			}
		}

		printf("Down\n");
		for(int i=0; i<row; i++)
		{
			for(int j=0; j<column; j++)
			{
				if(numbering[i][j] > 0 && (i == 0 || (i-1>=0 && puzzle[i-1][j] == '*')))
				{
					if(numbering[i][j] >= 10)
						printf(" %d.%c", numbering[i][j], puzzle[i][j]);
					else 
						printf("  %d.%c", numbering[i][j], puzzle[i][j]);
					// take care of it!
					for(int p=i+1; p<row&&puzzle[p][j]!='*'; p++)
						printf("%c", puzzle[p][j]);
					printf("\n");
				}
			}
		}
		// a result has been produced.
	}	/* END OF SCANF */
	// how to require, how to release!
	/*
	for(int i=0; i<last_row; i++)
	{
		free(numbering[i]);
		free(puzzle[i]);
	}
	free(numbering);
	free(puzzle);
	*/
}


