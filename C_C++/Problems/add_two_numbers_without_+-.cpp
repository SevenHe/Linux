#include <iostream>
using namespace std;

int getSum(int a, int b) {

cout << "a&b" << (a&b) << endl;
cout << "a^b" << (a^b) << endl;
	if ((a&b) == 0)

		return a^b;

	return getSum((a&b)<<1, a^b);

}

int main()
{
	int a, b;
	while (cin >> a >> b) {
		cout << a << " + " << b << " = " << getSum(a, b);
	}
	return 0;
}
