/*
DP idea, to handle the problems that judging the nums
such like, judge the prime numbers, or the square numbers, which are composed by "n" numbers.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int perfect_squares(int n)
{
	vector<int> dp(n+1, INT_MAX);

	// to avoid the influence of the min, remember!!!!
	dp[0] = 0;
	for (int i=0; i<n; i++) {
		for (int j=1; i+j*j<=n; j++) {
			dp[i+j*j] = min(dp[i+j*j], dp[i]+1);
		}
	}

	return dp[n];
}

int main()
{
	int nr;
	while (cin >> nr) {
		cout << perfect_squares(nr) << endl;
	}
	return 0;
}
