#include <iostream>
using namespace std;

typedef int* int_ptr;

int main()
{
	int *a, *b;
	int c, d;

	int_ptr e, f;
	a = &c;
	b = &d;
	e = &c;
	f = &d;

	return 0;
}
