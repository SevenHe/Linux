#include <stdio.h>

#define test_macro(x, y, z) ({ \
	const typeof(z) tm = x + y; \
	(z + tm); })

int main()
{
	int a = 1, b = 2, c = 3;
	int result;
	result = test_macro(a, b, c);
	printf("result is %d.\n", result);
}
