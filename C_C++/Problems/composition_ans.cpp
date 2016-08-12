#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int cnt = 0;

// composition, use the for loop to serialize them.
void dfs(vector<int>& x, int sum, int mul, int cur, int nr)
{
	if (cur >= x.size() || nr == x.size())
		return;
	/* 剪枝，从当前情况判断后面情况是否成立 */
	else if (nr > 1 && sum <= mul)
		return;

	/*
	 * 组合的解法：利用for循环，得到一个正确的解即进行下一步，
	 * 考虑特殊的情况，在本题中是１的情况
	 * 另外，既然是组合，在当前选择情况下，下一个选择不可重复，重复则无意义，因此
	 * 在选择的最后，加上重复判断－－解判断，特殊判断，重复判断
	 * 情况多的时候，分析剪枝的可能.
	 */
	for (int i=cur; i<x.size(); i++) {
		if (sum+x[i] > mul*x[i]) {
			cnt++;
			dfs(x, sum+x[i], mul*x[i], i+1, nr+1);
		}
		else if (x[i] == 1) {
			dfs(x, sum+1, mul, i+1, nr+1);
		}
		while (i<x.size()-1 && x[i] == x[i+1])
			i++;
	}
}

int main()
{
	int n;
	while (cin >> n) {
		vector<int> x(n);
		for (int i=0; i<n; i++)
			cin >> x[i];
		sort(x.begin(), x.end());
		dfs(x, 0, 1, 0, 0);
		cout << cnt << endl;
	}
	return 0;
}
