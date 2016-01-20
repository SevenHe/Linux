#include "calc.h"

double calculate(int n, int k)
{
	return factorial(n)/(factorial(k)*factorial(n-k));
}

double factorial(int n)
{
	double s = 1;
	int i;
	for(i=1; i<=n; i++)
		s = s * i;
	return s;
}
