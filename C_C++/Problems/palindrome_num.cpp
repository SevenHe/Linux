#include <iostream>
using namespace std;

bool isPalindrome(int x) {

	if (x < 0)
		return false;

	long long n = x;
	long long m = 10;
	int len = 1;
	while (n/m) {
		m *= 10;
		len++;
	}
	cout << "len: " << len << endl;
	m /= 10;
	long long m2 = 10;

	while (n > 0 && len > 0) {
			cout << "compare: " << n/m << ", " << n%m2*10/m2 << endl;
		if (n / m == n % m2 * 10 / m2) {
			n = n - n/m*m;
			n = n - n % m2 * 10 / m2;
			cout << "next n: " << n << endl;
			m /= 10;
			m2 *= 10;
			len -= 2;
			continue;
		}
		else
			return false;
	}

	return true;

}

int main()
{
	cout << "Get: " << isPalindrome(-2332423) << endl;
	cout << "Get: " << isPalindrome(1000000001) << endl;
	return 0;
}
