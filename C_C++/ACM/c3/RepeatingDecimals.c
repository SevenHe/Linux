#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _bool unsigned short
#define true 1
#define false 0
#define MAXP 50
#define MAXN 3000

int main()
{
	int member = 0;
	int denominator = 0;
	int factor[MAXP+1];
	short remainder[MAXN];

	// factor, think reversely, just << 1 / denominator, and get the quotient!
	while(scanf("%d %d", &member, &denominator) != EOF)
	{
		memset(factor, -1, sizeof(factor));
		memset(remainder, -1, sizeof(remainder));
		int count = 0;
		unsigned short loop_start = 0;
		unsigned short loop_end = 0;
		int ori_mem = member;
		// the integer partation
		int quotient = (int)(member / denominator);
		factor[count] = quotient;
		// the remainder partation
		remainder[member % denominator] = count;
		count ++;
		while(1)
		{
			member *= 10;
			if(count < 51)
				factor[count] = (int)(member / denominator) % 10;
			member = member % denominator;
			if(remainder[member] != -1)
			{
				loop_start = remainder[member];
				loop_end = count;
				//printf("start:%d, end:%d\n", loop_start, loop_end);
				break;
			}
			else
				remainder[member] = count;
			count ++;
		}
		printf("%d/%d = %d.", ori_mem, denominator, quotient);
		_bool is_printing_loop = false;
		if(loop_start == 0)
		{
			is_printing_loop = true;
			printf("(");
		}
		for(int i=1; i<MAXP+1; i++)
		{
			if(factor[i] == -1)
				break;
			else if(i == loop_start)
			{
				is_printing_loop = true;
				printf("%d(", factor[i]);
			}
			else
			{
				if(is_printing_loop)
				{
					if(i == MAXP && loop_end > MAXP + 1)
						printf("%d...)", factor[i]);
					else if(i != loop_end)
						printf("%d", factor[i]);
					else
						printf("%d)", factor[i]);
				}
				else
					printf("%d", factor[i]);
			}
		}
		printf("\n");
		// next line
		printf("   %d = number of digits in repeating cycle\n", loop_end - loop_start);
		printf("\n");
	}

	return 0;
}

