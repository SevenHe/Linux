#include<iostream>
#include<iterator>
#include<deque>
#include<algorithm>
using namespace std;

int main()
{
	ostream_iterator<int> out(cout, " ");

	int ia[] = {0, 1, 2, 3, 4, 5};
	deque<int> id(ia, ia+6);
	copy(id.begin(), id.end(), out);
	cout << endl;

	copy(id.rbegin(), id.rend(), out);
	cout << endl;
}
