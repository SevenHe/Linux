#include<stdio.h>

int main()
{
	double n = 2;
	double m = 4;
	double sum = 0.0;
	while(n <= m)
	{
		sum += (double)(1/(n*n));
		n += 1.0;
	}
	printf("result: %.5f\n", sum);
}
