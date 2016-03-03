#include<iostream>
using namespace std;

struct xx {
	long long _x1;
	char _x2;
	int _x3;
	char _x4[2];
	static int _x5;
};

int xx::_x5 = 0;

int main()
{
	int* p;
	char x[2];
	cout << "sizof(static int)=" << sizeof(xx::_x5) << endl;
	cout << "sizof(int)=" << sizeof(xx::_x3) << endl;
	cout << "sizof(long long)=" << sizeof(xx::_x1) << endl;
	cout << "sizof(char[2])=" << sizeof(x) << endl;
	cout << "sizeof(xx)=" << sizeof(xx) << endl;
	cout << "sizeof(*p)=" << sizeof(p) << endl;

	return 0;
}

