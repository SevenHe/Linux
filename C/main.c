#include <stdio.h>
#include "define.h"
#include "getdata.h"
#include "putdata.h"
#include "calc.h"

int main()
{
	int n,k;
	double c;
	getdata(&n, &k);
	c = calculate(n, k);
	putdata(n, k, c);
}
