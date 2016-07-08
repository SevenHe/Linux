#include <iostream>
using namespace std;

int main()
{
	int a[10][10];
	cout << sizeof(a) << endl;
	cout << sizeof(&a) << endl;
	cout << sizeof(a[5]) << endl;
	cout << sizeof(&a[5]) << endl;
	cout << sizeof(a[5][5]) << endl;
	cout << sizeof(&a[5][5]) << endl;

	return 0;
}
