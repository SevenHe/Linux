#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define bool unsigned short
#define true 1
#define false 0

int main()
{
	double A[10][31];
	long long B[10][31];
	// think reversely, just 300 kinds, so make a table and find the answer in it
	for(int i=0; i<10; i++)
	{
		for(int j=1; j<31; j++)
		{
			// m * 2 ^ e = A * 10 ^ B;
			double m = 1 - pow(2, -1-i);
			double e = pow(2, j) - 1;
			// t = log10(A) + B, 0 < A < 10, so log10(A) < 1, it is the fraction
			double t = log10(m) + e * log10(2);
			// integer part
			B[i][j] = t;
			A[i][j] = pow(10, t-B[i][j]);
		}
	}
			
	char *input;
	char a[31];
	input = a;
	while(scanf("%s", input) != EOF && strcmp(input, "0e0"))
	{
		//printf("%s\n", input);
		char number[31];
		int factorial = 0;
		int len = strlen(input);
		for(int i=0; i<len; i++)
		{
			if(input[i] != 'e')
				number[i] = input[i];
			else
			{
				int strlen = len;
				len = i;
				for(int j=i+1; j<strlen; j++)
				{
					factorial *= 10;
					factorial += (int)(input[j]-'0');
				}
				break;
			}
		}
		double fraction = strtod(number, NULL);
		//printf("%lf, %d\n", fraction, factorial);		
		while(fraction < 1)
		{
			fraction *= 10;
			factorial -= 1;
		}
		bool end = false;
		for(int i=0; i<10 && !end; i++)
		{
			for(int j=1; j<31; j++)
			{
				//printf("table: A -- %f, B -- %lld\n", A[i][j], B[i][j]);
				if(B[i][j] == factorial && fabs(fraction - A[i][j]) < 1e-4)
				{
					printf("%d %d\n", i, j);
					end = true;
					break;
				}
			}
		}
	}

	return 0;
}
