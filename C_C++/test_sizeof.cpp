#include<iostream>
using namespace std;

struct xx {
	long long _x1;
	char _x2;
	int _x3;
	char _x4[2];
	static int _x5;
};

struct xy {
	long long _x1;
	char _x4[2];
	char _x2;
	int _x3;
	static int _x5;
};

union yy {
	char _y1[2];
	unsigned short _y2;
};

int xx::_x5 = 0;

int main()
{
	int* p;
	char x[2];
	FILE* fp;
	cout << "sizof(static int)=" << sizeof(xx::_x5) << endl;
	cout << "sizof(int)=" << sizeof(xx::_x3) << endl;
	cout << "sizof(long long)=" << sizeof(xx::_x1) << endl;
	cout << "sizof(char[2])=" << sizeof(x) << endl;
	cout << "sizeof(xx)=" << sizeof(xx) << endl;
	cout << "sizeof(xy)=" << sizeof(xy) << endl;
	cout << "sizeof(*p)=" << sizeof(p) << endl;
	cout << "sizeof(FILE*)=" << sizeof(fp) << endl;
	cout << "sizeof(union)=" << sizeof(yy) << endl;

	return 0;
}

