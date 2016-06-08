#include <stdio.h>

struct sl {
	void (*func)(int);
};

void test(int a)
{
	printf("%d\n", a);
}

void func2(void)
{
	printf("func2 ok!\n");
}

typedef void (*fc)(void);
void test2(fc test3)
{
	test3();
}

int main()
{
	struct sl msl = {
		.func = test
	};

	msl.func(5);
	test2(func2);
	return 0;
}

