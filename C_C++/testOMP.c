#include <omp.h>
#include <stdio.h>

int A = 100;

void test()
{
#pragma omp parallel for	
	for(int i=0; i<10; i++)
	{
		A = i;
		printf("Thread ID: %d, %d: %d\n", omp_get_thread_num(), i, A);
	}
	printf("Global A: %d\n", A);

#pragma omp parallel for 
	for(int i=0; i<10; i++)
	{
		A ++;
		printf("Thread ID: %d, %d: %d\n", omp_get_thread_num(), i, A);
	}

	printf("Global A: %d\n", A);
}


int main()
{
	int A = 100;
#pragma omp parallel for firstprivate(A)
	for(int i=0; i<10; i++)
	{
		printf("Thread ID: %d, %d: %d\n", omp_get_thread_num(), i, A);
		A = i;
	}
	printf("%d\n", A);

	test();
	return 0;
}
