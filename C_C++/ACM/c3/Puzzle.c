#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _bool int
#define true 1
#define false 0
#define us unsigned short

typedef struct msg_ll {
	char* msg;
	struct msg_ll* next;
}msg_ll;

int main()
{
	char puzzle[5][5];
	char* input = (char*)malloc(sizeof(char)*32);
	_bool isPuzzle = true;
	short puzzle_index = 0;
	us count = 1;
	us pri_row = 0;
	us pri_column = 0;
	//msg_ll* head;
	while(fgets(input, sizeof(input), stdin))
	{
		if(input[0] == 'Z' && (input[1] == '\n' || input[1] == '\0'))
			break;
		if(isPuzzle)
		{
			for(int i=0; i<5; i++)
			{
				if(input[i] == ' ')
				{
					pri_row = puzzle_index;
					pri_column = i;
				}
				puzzle[puzzle_index][i] = input[i];
			}
			puzzle_index ++;
			//printf("puzzle_index : %d\n", puzzle_index);
		}
		//fflush(stdin);
		// start to get the order
		if(puzzle_index == 5)
		{
			_bool has_error = false;
			_bool is_end = false;
			/*msg_ll* msgn = (msg_ll*)malloc(sizeof(msg_ll));
			if(count == 1)
			{
				head = msgn;
				head->msg = (char*)malloc(sizeof(char)*200);
				head->next = NULL;
			}
			else
			{	
				msg_ll* ll = head;
				while(ll->next != NULL)
					ll = ll->next;
				ll->next = msgn;
				msgn->msg = (char*)malloc(sizeof(char)*200);
				msgn->next = NULL;
			}*/
			char* order = (char*)malloc(sizeof(char)*32);
			while(!is_end && scanf("%s", order))
			{
				int len = strlen(order);
				//char cache[64] = "";
				//printf("get order: %s\n", order);
				for(int c=0; c<len; c++)
				{
					int temp;
					switch(order[c])
					{
						case 'A':
							if(pri_row - 1 < 0)
							{
								has_error = true;
								break;
							}
							else
							{
								temp = puzzle[pri_row-1][pri_column];
								puzzle[pri_row-1][pri_column] = ' ';
								puzzle[pri_row][pri_column] = temp;
								pri_row = pri_row -1;
								//printf("exchange [%d][%d] with [%d][%d]\n", pri_row+1, pri_column, pri_row, pri_column);
							}
							break;
						case 'B':
							if(pri_row + 1 > 4)
							{
								has_error = true;
								break;
							}
							else
							{
								temp = puzzle[pri_row+1][pri_column];
								puzzle[pri_row+1][pri_column] = ' ';
								puzzle[pri_row][pri_column] = temp;
								pri_row = pri_row + 1;
								//printf("exchange [%d][%d] with [%d][%d]\n", pri_row-1, pri_column, pri_row, pri_column);
							}
							break;
						case 'L':
							if(pri_column - 1 < 0)
							{
								has_error = true;
								break;
							}
							else
							{
								temp = puzzle[pri_row][pri_column-1];
								puzzle[pri_row][pri_column-1] = ' ';
								puzzle[pri_row][pri_column] = temp;
								pri_column = pri_column - 1;
								//printf("exchange [%d][%d] with [%d][%d]\n", pri_row, pri_column+1, pri_row, pri_column);
							}
							break;
						case 'R':
							if(pri_column + 1 > 4)
							{
								has_error = true;
								break;
							}
							else
							{
								temp = puzzle[pri_row][pri_column+1];
								puzzle[pri_row][pri_column+1] = ' ';
								puzzle[pri_row][pri_column] = temp;
								pri_column = pri_column + 1;
								//printf("exchange [%d][%d] with [%d][%d]\n", pri_row, pri_column-1, pri_row, pri_column);
							}
							break;
						case '0':
							if(count == 1)
								printf("Puzzle #%d:\n", count);
							//	sprintf(cache, "Puzzle #%d:\n", count);
							else
								printf("\nPuzzle #%d:\n", count);
							//	sprintf(cache, "\nPuzzle #%d:\n", count);
							//strcat(msgn->msg, cache); 
							count ++;
							if(has_error)
								printf("This puzzle has no final configuration.\n");
							//	strcat(msgn->msg, "This puzzle has no final configuration.\n");
							else
							{
								for(int pr=0; pr<5; pr++)
								{
									//memset(cache, 0, sizeof(char)*64);
									for(int pc=0; pc<5; pc++)
									{
										if(pc != 4)
											printf("%c ", puzzle[pr][pc]);
										else
											printf("%c", puzzle[pr][pc]);
										//sprintf(cache, "%c ", puzzle[pr][pc]);
										//strcat(msgn->msg, cache);
									}
									printf("\n");
									//strcat(msgn->msg, "\n");
								}
							}
							getchar();
							is_end = true;
							memset(puzzle, 0, sizeof(puzzle));
							break;
					}
				}
			}
			free(order);
			puzzle_index = 0;
		}	/* END OF A PUZZLE */
	}

	/*
	msg_ll* del;
	while(head != NULL)
	{
		printf("%s", head->msg);
		del = head->next;
		free(head);
		head = del;
	}
	*/

	free(input);
}
								

