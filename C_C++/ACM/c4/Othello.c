/*
 * For this case, i know the most important problem, that is every part should be decoupled
 * if 2 parts get into each other, may cause some problems that you do not know via the variables
 * and take care of the global variables!
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>	/* for uint16_t ... */
#include<stddef.h>	/* size_t */

#define MAXLINE 8
#define bool uint16_t
#define true 1
#define false 0

char board[MAXLINE+5][MAXLINE+5];
bool can_move[MAXLINE+5][MAXLINE+5];
/* carry[0] for black player to judge if he can move anywhere, carry[1] for white. */
bool carry[2];
/* type[0] for black, type[1] for white */
char type[2] = {'B', 'W'};
/* move successfully or not */
bool is_successful[2];
/* for formatting */
bool first;
typedef enum Direction{L,LU,U,RU,R,RD,D,LD}Direction;

void print_board()
{
	/*
	 * sometimes, if you print a \n here, it may exist in the cache, 
	 * and print again at the point you do not know.
	 */
	for(int i=1; i<MAXLINE+1; i++)
	{
		printf("%s\n", &(board[i][1]));
	}
}

void count_board()
{
	int t1 = 0;
	int t2 = 0;
	for(int i=1; i<MAXLINE+1; i++)
		for(int j=1; j<MAXLINE+1; j++)
		{
			if(board[i][j] == type[0])
				t1 ++;
			else if(board[i][j] == type[1])
				t2 ++;
		}
	printf("Black - %2d White - %2d\n", t1, t2);
}

void operate(char t, char cmd, Direction d, int row, int column, bool couple)
{
	int step[2];
	switch(d)
	{
		case L:
			step[0] = 0;
			step[1] = -1;
			break;
		case LU:
			step[0] = -1;
			step[1] = -1;
			break;
		case U:
			step[0] = -1;
			step[1] = 0;
			break;
		case RU:
			step[0] = -1;
			step[1] = 1;
			break;
		case R:
			step[0] = 0;
			step[1] = 1;
			break;
		case RD:
			step[0] = 1;
			step[1] = 1;
			break;
		case D:
			step[0] = 1;
			step[1] = 0;
			break;
		case LD:
			step[0] = 1;
			step[1] = -1;
			break;
	}
	int start_row = row;
	int start_column = column;
	bool start = false;
	int temp_row[9];
	int temp_column[9];
	int index = 0;
	row += step[0];
	column += step[1];
	while(row >= 1 && row <= 8 && column >= 1 && column <= 8)
	{
		if(cmd == 'M')
		{
			//printf("diretion %d\n", d);
			//printf("move %c: %d, %d\n", t, row, column);
			if(t == type[0] && !start)
			{
				if(!carry[0])
				{
					t = type[1];
					start = true;
				}
			}
			else if(!carry[1] && !start)
			{
				t = type[0];
				start = true;
			}
			// think the border, do not change the status.
			if(board[row][column] != '-' && board[row][column] != t)
			{
				//printf("ready change %d %d from %c to %c\n", row, column, t == type[0] ? type[1] :type[0], t);
				temp_row[index] = row;
				temp_column[index] = column;
				index ++;
				//printf("testok!\n");
			}
			else if(board[row][column] == t)
			{
				for(int k=0; k<index; k++)
				{
					//printf("really change %d %d\n", temp_row[k], temp_column[k]);
					board[temp_row[k]][temp_column[k]] = t;
				}
				if(t == type[0])
					is_successful[0] = true;
				else
					is_successful[1] = true;
				break;
			}
			// all situations, no doubt
			else if(board[row][column] == '-')
				break;
		}
		else if(cmd == 'L')
		{
			// this situation, row and column should be the first position
			if(can_move[start_row][start_column])
				break;
			if((board[row][column] == t && !start) || board[row][column] == '-')
				break;
			else if(board[row][column] != t && !start)
			{
				start = true;
			}
			else if(board[row][column] == t && start)
			{
				if(!can_move[start_row][start_column])
				{
					if(first && !couple)
					{
						printf("(%d,%d)", start_row, start_column);
						first = false;
					}
					else if(!couple)
						printf(" (%d,%d)", start_row, start_column);
				}
				can_move[start_row][start_column] = true;
				if(t == type[0])
					carry[0] = true;
				else
					carry[1] = true;
			}
		}
		row += step[0];
		column += step[1];
	}
}

int main()
{
	//size_t len = MAXLINE;
	//uint16_t W;
	//uint16_t B;
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
	{
		// formatting
		if(i > 0)
			printf("\n");
		memset(can_move, 0, sizeof(can_move));
		memset(carry, 0, sizeof(carry));
		memset(is_successful, 0, sizeof(is_successful));
		char cmd[10];
		memset(cmd, 0, sizeof(cmd));
		for(int j=1; j<MAXLINE+1; j++)
		{
			scanf("%s", &(board[j][1]));
			getchar();
			//printf("%s\n", board[i]);
		}
		char player;
		scanf("%c", &player);
		//printf("player: %s\n", player == 'W' ? "White" : "Black");
		// if not equal to "Q", strcmp would return a true value
		while(scanf("%s", cmd) != EOF && strcmp(cmd, "Q"))
		{
			// There is a problem that L and M are coupled, but this is a bad way.
			// a \n
			getchar();
			int impermanent = 0;
			char temp_cmd = cmd[0];
			bool couple;
		  while(impermanent < 2)
		  {	
			if(impermanent == 0)
			{
				cmd[0] = 'L';
				couple = true;
			}
			else
			{
				cmd[0] = temp_cmd;
				couple = false;
			}
			switch(cmd[0])
			{
				case 'L':
				{
					first = true;
					// carry is changing for every case!
					// also for other global variables!
					carry[0]=carry[1]=false;
					for(int r=1; r<MAXLINE+1; r++)
						for(int c=1; c<MAXLINE+1; c++)
						{
							if(board[r][c] != '-')
								continue;
							operate(player, cmd[0], L, r, c, couple);
							operate(player, cmd[0], LU, r, c, couple);
							operate(player, cmd[0], U, r, c, couple);
							operate(player, cmd[0], RU, r, c, couple);
							operate(player, cmd[0], R, r, c, couple);
							operate(player, cmd[0], RD, r, c, couple);
							operate(player, cmd[0], D, r, c, couple);
							operate(player, cmd[0], LD, r, c, couple);
						}
					//printf("\ncurrent player: %c\n", player);
					if(player == type[0] && !couple)
					{
						if(carry[0])
							printf("\n");
						else
							printf("No legal move.\n");
					}
					else if(player == type[1] && !couple)
					{
						if(carry[1])
							printf("\n");
						else
							printf("No legal move.\n");
					}
					// reset the can move
					memset(can_move, 0, sizeof(can_move));
					break;
				}
				case 'M':
				{
					int row = (int)(cmd[1] - '0');
					int column = (int)(cmd[2] - '0');
					is_successful[0]=is_successful[1]=false;
					operate(player, cmd[0], L, row, column, couple);
					operate(player, cmd[0], LU, row, column, couple);
					operate(player, cmd[0], U, row, column, couple);
					operate(player, cmd[0], RU, row, column, couple);
					operate(player, cmd[0], R, row, column, couple);
					operate(player, cmd[0], RD, row, column, couple);
					operate(player, cmd[0], D, row, column, couple);
					operate(player, cmd[0], LD, row, column, couple);
					if(is_successful[0])
					{
						player = type[1];
						// add the move piece
						board[row][column] = type[0];
						is_successful[0] = false;
					}
					else if(is_successful[1])
					{
						player = type[0];
						// just like above
						board[row][column] = type[1];
						is_successful[1] = false;
					}
					count_board();
					//print_board();
					break;
				}
			}
			impermanent ++;
		  }
		}
		print_board();
	}

	return 0;
}
