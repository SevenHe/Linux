#include<stdio.h>

int main()
{
	int a = 1;
	int b = 6;
	int precision = 4;
 	// newton iteration can do this for precision big enough, but a little complex
	// double for .16f
	double result = (double)a/b;
	// get it up
	int temp = precision;
	while(temp >= 0)
	{
		result *= 10;
		temp -= 1;
	}
	a = (int)result;
	if((a % 10) >= 5)
		a += 10;
	result = (double)a;
	result /= 10;
	result = (int)result;
	// float it
	while(precision > 0)
	{
		result /= 10;
		precision -= 1;
	}
	printf("%g\n", result);
	return 0;
}
