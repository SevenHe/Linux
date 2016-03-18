#include<iostream>
#include<iterator>
#include<deque>
#include<algorithm>
using namespace std;

class Test {
	public:
		inline int operator()(int value) { 
			cout << "Get in the overload function!" << endl; 
			return value; 
		}
};

int main()
{
	ostream_iterator<int> out(cout, " ");

	int ia[] = {0, 1, 2, 3, 4, 5};
	deque<int> id(ia, ia+6);
	copy(id.begin(), id.end(), out);
	cout << endl;

	copy(id.rbegin(), id.rend(), out);
	cout << endl;

	Test a;

	cout << "Test: " << Test()(20) << "and Test: " << a(15) << endl;
}
