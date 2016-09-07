#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 从Ｓ字符串的子串中找出能出现多少次Ｔ，字符的相对位置不变
// 解题思路，利用O(n)的空间，保存T[0, j]在Ｓ中已经出现了多少次，然后取比较后面即可．
int dp(const string& S, const string& T)
{
	vector<int> f(T.size()+1, 0);
	f[0] = 1;

	// 动态规划的思路，用到f[j]是上一轮循环的，生成本轮新的f[j],因此用从后想前遍历！！
	// 普遍思路，用f[j+1]更新后的，从后到前，否则从前到后
	// 用f[j-1]或者f[j]生成f[j+1]更新前的，从后到前，否则从前到后！
	for (int i=0; i<S.size(); i++)
		for (int j=T.size()-1; j>=0; j--)
			f[j+1] += (S[i] == T[j]) ? f[j] : 0;

	return f[T.size()];
}

int main()
{
	string S, T;
	while (cin >> S >> T) {
		cout << "Ans: " << dp(S, T) << endl;
	}
	return 0;
}

