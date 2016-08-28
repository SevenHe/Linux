#include <iostream>
using namespace std;

int nr;

int guess(int num)
{
	if (nr > num)
		return 1;
	else if (nr < num)
		return -1;
	return 0;
}

int guessNumber(int n) {

/* may overflow, use long long */
	long long left = 1;
	long long right = n;
	int gus;

	while (1) {
		gus = (left + right) >> 1;
		cout << "Guess: " << gus << endl;
		int ret = guess(gus);
		if (ret == -1) {
			right = gus - 1;
		}
		else if (ret == 1) {
			left = gus + 1;
		}
		else if (ret == 0)
			break;
	}

	return gus;
}

int main()
{
	int range;
	while (cin >> range >> nr) {
		guessNumber(range);
	}
	return 0;
}
