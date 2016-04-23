#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void checkmate(int (*board)[10], int row, int column)
{
	if(board[row][column] == 0)
		board[row][column] = 1;
	else if(board[row][column] == 3)
		board[row][column] = 4;
	else if(board[row][column] == 2)
		board[row][column] = 5;
}

/*
 * a more better way is to divied the situations by different pieces checkmating. 
 * all adjustment should appear after a board completion!
 * for another day to complete this.
 */
int main()
{
	// 0 for no change, 2 for black general position, 1 for red checkmate position, 3 for red pieces
	// 4 for checkmate and piece position, 5 for black general having been threadten
	int board[11][10];
	// final handle the cannon
	int cannon_row[7];
	int cannon_column[7];
	// chariot_row/column
	// horse_row/column
	int n = 0;
	int black_row, black_column;
	int red_row, red_column;
	black_row = black_column = 0;
	// 'G' for general, 'R' for chariot, 'H' for horse, 'C' for cannon
	while(scanf("%d %d %d", &n, &black_row, &black_column) != EOF && n != 0 
			&& black_row != 0 && black_column != 0)
	{
		memset(board, 0, sizeof(board));
		memset(cannon_row, 0, sizeof(cannon_row));
		memset(cannon_column, 0, sizeof(cannon_column));
		board[black_row][black_column] = 2;
		unsigned short cannon_index = 0;
		//printf("%d %d %d\n", n, black_row, black_column);
		for(int i=0; i<n; i++)
		{
			char type;
			int row = 0;
			int column = 0;
			// \n
			getchar();
			type = getchar();
			scanf("%d", &row);
			scanf("%d", &column);
			switch(type)
			{
				case 'R':
					for(int j=1; j<11; j++)
						checkmate(board, j, column);
					for(int j=1; j<10; j++)
						checkmate(board, row, j);
					break;
				case 'H':
					// top
					if(column - 1 >= 1 && row - 2 >= 1 && !board[row-1][column])
						checkmate(board, row-2, column-1);
					if(column + 1 <= 9 && row - 2 >= 1 && !board[row-1][column])
						checkmate(board, row-2, column+1);
					// right
					if(column + 2 <= 9 && row - 1 >= 1 && !board[row][column+1])
						checkmate(board, row-1, column+2);
					if(column + 2 <= 9 && row + 1 <= 10 && !board[row][column+1])
						checkmate(board, row+1, column+2);
					// bottom
					if(column + 1 <= 9 && row + 2 <= 10 && !board[row+1][column])
						checkmate(board, row+2, column+1);
					if(column - 1 >= 1 && row + 2 <= 10 && !board[row+1][column])
						checkmate(board, row+2, column-1);
					// left
					if(column - 2 >= 1 && row - 1 >= 1 && !board[row][column-1])
						checkmate(board, row-1, column-2);
					if(column - 2 >= 1 && row + 1 <= 10 && !board[row][column-1])
						checkmate(board, row+1, column-2);
					break;
				case 'C':
					cannon_row[cannon_index] = row;
					cannon_column[cannon_index] = column;
					cannon_index ++;
					//printf("get a cannon: %d, %d\n", row, column);
					
					break;
				case 'G':
					red_row = row;
					red_column = column;
					int find_one = 0;
					for(int i=red_row-1; i>black_row; i--)
					{
						printf("get %d %d: %d\n", i, column, board[i][column]);
						if(board[i][column] != 0 && board[i][column] != 1 && board[i][column] != 2)
							find_one = 1;
					}
					if(find_one)
						break;
					else
					{
						printf("inflict!\n");
						checkmate(board, 1, column);
						checkmate(board, 2, column);
						checkmate(board, 3, column);
					}
					break;
			}
			if(board[row][column] == 1)
				board[row][column] = 4;
			else
				board[row][column] = 3;
		}
		int row;
		int column;
		for(int i=0; i<cannon_index; i++)
		{
			row = cannon_row[i];
			column = cannon_column[i];
			//printf("get into cannons: %d, %d\n", row, column);
			// row right
			for(int j=column+1; j<10; j++)
			{
				if(board[row][j] == 2 || board[row][j] == 5)
					break;
				// do not think the situation that blacks are the stepping-stones
				if(board[row][j] == 3 || board[row][j] == 4)
				{
					for(int k=j+1; k<10; k++)
					{
						//printf("update %d %d: %d\n", row, k, board[row][k]);
						if(board[row][k] != 0 && board[row][k] != 1 && board[row][k] != 2)
							break;
						else
							checkmate(board, row, k);
					}
					break;
				}
			}
			// row left
			for(int j=column-1; j>0; j--)
			{
				if(board[row][j] == 2 || board[row][j] == 5)
					break;
				if(board[row][j] == 3 || board[row][j] == 4)
				{
					for(int k=j-1; k>0; k--)
					{
						if(board[row][k] != 0 && board[row][k] != 1 && board[row][k] != 2)
							break;
						else
							checkmate(board, row, k);
					}
					break;
				}
			}	
			// column down 
			for(int j=row+1; j<11; j++)
			{
				if(board[row][j] == 2 || board[row][j] == 5)
					break;
				if(board[j][column] == 3 || board[j][column] == 4)
				{
					for(int k=j+1; k<11; k++)
					{
						if(board[k][column] != 0 && board[k][column] != 1 && board[k][column] != 2)
							break;
						else
							checkmate(board, k, column);
					}
					break;
				}
			}
			// column up
			for(int j=row-1; j>0; j--)
			{
				if(board[row][j] == 2 || board[row][j] == 5)
					break;
				if(board[j][column] == 3 || board[j][column] == 4)
				{
					//printf(" get a cushion: %d, %d\n", j, column);
					for(int k=j-1; k>0; k--)
					{
						//printf("update %d %d: %d\n", j, k, board[k][column]);
						if(board[k][column] != 0 && board[k][column] != 1 && board[k][column] != 2)
							break;
						else
							checkmate(board, k, column);
					}
					break;
				}
			}
			if(board[row][column] == 1)
				board[row][column] = 4;
			else
				board[row][column] = 3;
		}
		// get the solution, based on the black row and column.
		unsigned short end = 0;
		row = black_row;
		column = black_column;
		if(row - 1 >= 1 && (board[row-1][column] == 1 || board[row-1][column] == 4))
			end += 1;
		else if(row - 1 < 1)
			end += 1;
		if(column - 1 >= 4 && (board[row][column-1] == 1 || board[row][column-1] == 4))
			end += 1;
		else if(column - 1 < 4)
			end += 1;
		if(column + 1 <= 6 && (board[row][column+1] == 1 || board[row][column+1] == 4))
			end += 1;
		else if(column + 1 > 6)
			end += 1;
		if(row + 1 <= 3 && (board[row+1][column] == 1 || board[row+1][column] == 4))
			end += 1;
		else if(row + 1 > 3)
			end += 1;
		int is_hedging = 1;
		if(red_column == black_column)
		{
			for(int j=black_row+1; j<red_row; j++)
			{
				if(board[j][red_column] == 3 && board[j][red_column] == 4)
				{
					is_hedging = 0;
					printf("not hedging!\n");
					break;
				}
			}
		}
		if(end == 4 && !is_hedging)
			printf("YES\n");
		else
			printf("NO\n");
		for(int j=1; j<11; j++)
		{
			for(int k=1; k<10; k++)
				printf("%d ", board[j][k]);
			printf("\n");
		}
	}
	return 0;
}
