#include<iostream>
using namespace std;

class Test 
{
	public:
		static int count;
		Test();
};

//*************************--accomplish--********************************
int Test::count = 1;
Test::Test()
{
	cout << "This is " << count << " invocation!" << endl;
	count ++;
}
int main()
{
	Test a[5], *b[6];
	
	cout << b[0];
	return 0;
}
