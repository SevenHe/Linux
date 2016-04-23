#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char board[11][10];
	int n;
	int black_row;
	int black_column;
	while(scanf("%d %d %d", &n, &black_row, &black_column) != EOF &&
			n != 0 && black_row != 0 && black_column != 0)
	{
		memset(board, 'E', sizeof(board));
		board[black_row][black_column] = 'B';
		for(int i=0; i<n; i++)
		{
			int row = 0;
			int column = 0;
			getchar();
			char type = getchar();
			scanf("%d", &row);
			scanf("%d", &column);
			board[row][column] = type;
		}
		for(int i=1; i<11; i++)
		{
			for(int j=1; j<10; j++)
			{
				switch(board[i][j])
				{
					// Empty
					case 'E':
						break;
					// Chariot
					case 'R':
						break;
					// Horse:
					case 'H':
						break;
					// Cannon:
					case 'C':
						break;
					// General
					case 'G':
					 	break;
					// Checkmate -- Kill
					case 'K':
						break;
				}
			}
		}
		// get the solution

	}

	return 0;
}
