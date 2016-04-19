#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _bool unsigned short
#define true 1
#define false 0

int main()
{
	int box[6][2];
	// judging data as a pallet is a better way!
	while(scanf("%d %d", &box[0][0], &box[0][1]) != EOF)
	{
		int edge[3];
		int count[3];
		int index = 0;
		memset(edge, 0, sizeof(edge));
		memset(count, 0, sizeof(count));
		if(box[0][0] != box[0][1])
		{
			edge[0] = box[0][0];
			edge[1] = box[0][1];
			count[0] = 1;
			count[1] = 1;
			index += 2;
		}
		else
		{
			edge[0] = box[0][0];
			count[0] = 2;
			index ++;
		}
		for(int i=1; i<6; i++)
		{
			scanf("%d %d", &box[i][0], &box[i][1]);
			//printf("get two edges: %d %d\n", box[i][0], box[i][1]);
			unsigned short e1 = 0;
			unsigned short e2 = 0;
			for(int j=0; (e1^1 || e2^1) && j<3; j++)
			{
				if(box[i][0] == edge[j] && e1^1)
				{
					count[j] ++;
					//printf("edge: %d ++\n", box[i][0]);
					e1 = 1;
				}
				else if(edge[j] == 0 && e1^1)
				{
					if(index < 3)
					{
						edge[index] = box[i][0];
						count[index] = 1;
						index ++;
						//printf("add an edge: %d\n", box[i][0]);
					}
					e1 = 1;
				}
				if(box[i][1] == edge[j] && e2^1)
				{
					count[j] ++;
					e2 = 1;
					//printf("edge: %d ++\n", box[i][1]);
				}
				else if(edge[j] == 0 && e2^1)
				{
					if(index < 3)		
					{
						edge[index] = box[i][1];
						count[index] = 1;
						index ++;
						//printf("add an edge: %d\n", box[i][1]);
					}
					e2 = 1;
				}
			}
		}
		// judgement
		if(count[0] == count[1] && count[1] == count[2] && count[2] == 4)
		{
			_bool error = false;
			for(int i=0; i<6; i++)
			{
				if(box[i][0] == box[i][1])
				{
					error = true;
					break;
				}
			}
			if(error)
				printf("IMPOSSIBLE\n");
			else
				printf("POSSIBLE\n");
		}
		else if((count[0] == 8 && count[1] == 4) || (count[1] == 8 && count[0] == 4))
		{
			unsigned short diff = 0;
			for(int i=0; i<6; i++)
			{
				if(box[i][0] != box[i][1])
					diff ++;
			}
			if(diff == 4)
				printf("POSSIBLE\n");
			else
				printf("IMPOSSIBLE\n");
		}
		else if(count[0] == 12)
			printf("POSSIBLE\n");
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}
