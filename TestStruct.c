#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_Y 10
#define MAX_X 10

typedef struct test 
{
	int id;
}test_t;

test_t test[10];

int main()
{	
	struct test *tp;
	int i=0;
	for(i=0; i<10; i++){
		test[i].id = i;
		printf("INIT ID: %d \n", test[i].id); 
	}
	test->id = 10;
	printf("TEST ID: %d \n", test->id);
	tp = test;
	tp = (++tp);
	tp->id = 20;
	printf("TEST ID: %d \n", tp->id);
	printf("TEST ID: %d \n", tp->id);
	tp = test;
	tp = (++tp);
	printf("TEST ID: %d \n", tp->id);
	char buf[20] = "None";
	strcpy(buf, "empty");
	printf("buf: %s \n", buf);
	srand((unsigned)time(NULL));
	printf("%d!!", rand() % 9);
	return 0;
}

test_t* convert(int a[MAX_Y][MAX_X])
{
	return NULL;
}