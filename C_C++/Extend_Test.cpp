#include<iostream>
#include<unistd.h>
using namespace std;

class Base
{
	int x;
	public:
	Base(int b):x(b) { cout << "Base initialization!" << endl; }
	virtual void display()
	{
		cout << x << endl;
	}
};

class Derived:public Base
{
	int y;
	public:
	Derived(int d):Base(d), y(d) { cout << "Derived initialization!" << endl; }
	void display()
	{
		cout << y << endl;
	}
};

int main()
{
	Base b(2);
	Derived d(3);
	b.display();
	d.display();
	Base *p = &d;
	p->display();

	pause();
	return 0;
}
