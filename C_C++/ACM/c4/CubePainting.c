#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define bool unsigned short
#define true 1
#define false 0

int main()
{
	char ts[15];
	char cube1_side[3], cube1_opposite[3];
	char cube2_side[3], cube2_opposite[3];
	while(scanf("%s", ts) != EOF)
	{
		//printf("get: %s\n", ts);
		for(int i=0; i<3; i++)
		{
			cube1_side[i] = '\0';
			cube1_opposite[i] = '\0';
			cube2_side[i] = '\0';
			cube2_opposite[i] = '\0';
		}
		for(int i=0; i<3; i++)
		{
			cube1_side[i] = ts[i];
			cube1_opposite[i] = ts[5-i];
			cube2_side[i] = ts[i+6];
			cube2_opposite[i] = ts[11-i];
			//printf(" %c, %c, %c, %c\n", cube1_side[i], cube1_opposite[i], cube2_side[i], cube2_opposite[i]);
		}
		int index = 0;
		int mapping[3];
		memset(mapping, -1, sizeof(mapping));
		bool end = false;
		while(!end)
		{
			for(int i=0; i<3; i++)
			{
				if(((cube1_side[index] == cube2_side[i] &&
					cube1_opposite[index] == cube2_opposite[i]) || (
					cube1_side[index] == cube2_opposite[i] && 
					cube1_opposite[index] == cube2_side[i]))  && mapping[i] == -1)
				{
					mapping[i] = index;
					//printf("mapping %d --> %d \n", i, index);
					break;
				}
			}
			index ++;
			if(index == 3)
				end = true;
		}
		if(mapping[0] != -1 && mapping[1] != -1 && mapping[2] != -1)
		{
			printf("TRUE\n");
		}
		else
			printf("FALSE\n");
	}

	return 0;
}
