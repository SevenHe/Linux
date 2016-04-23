#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int row;
	int column;
	while(scanf("%d %d", &row, &column) != EOF)
	{
		int** square = (int**)calloc(row, sizeof(int)*column);
		// get m lines

		// judge the number

		// get the solution

		free(square);
	}

	return 0;
}
