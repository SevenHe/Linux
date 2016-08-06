#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
#include <sstream>
using namespace std;

int cnt = 0;
set<long long> sset;

void permutation(vector<int>& a, vector<int> flag, int len, int n, int cur)
{
	if (len == n) {
		long long sum = 0;
		long long mul = 1;
		int count = 0;
		for (int i=0; i<n; i++) {
			if (flag[i] == 1) {
				cout << i << ":" << a[i] << endl;
				sum += a[i];
				mul *= a[i];
				count++;
			}
		}
		cout << "get sum:" << sum << endl;
		if (count == 0 || !sset.insert(sum).second)
			return;
		if (sum > mul)
			cnt++;
		return;
	}
	for (int i=cur+1; i<n; i++) {
		flag[i] = 1;
		permutation(a, flag, len+1, n, i);
		flag[i] = 0;
		permutation(a, flag, len+1, n, i);
	}
}

int main()
{
	int n;
	while (cin >> n) {
		cnt = 0;
		vector<int> nr(n);
		vector<int> flag(n);
		for (int i=0; i<n; i++) {
			cin >> nr[i];
			flag[i] = 0;
		}
		permutation(nr, flag, 0, n, -1);
		cout << cnt << endl;
	}
	return 0;
}
