#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool flag[10] = {0};

void combination(vector<int>& a, int cur)
{
	if (cur == a.size()) {
		for (int i=0; i<a.size(); i++) {
			if (flag[i])
				cout << a[i] << " ";
		}
		cout << endl;
		return;
	}
	/*
	易于理解，每次选择或者不选择该数，都进行下一项
	flag[cur] = true;
	combination(a, cur+1);
	flag[cur] = false;
	combination(a, cur+1);
	*/
	/*
	 * 该循环遍历了所有选择的情况，根据上一个选择的，进行下一个选择或者不选择
	 * 唯一要修复的地方就是，最后一个数的false的情况没有打印，因为没进入最后的个数判断
	 * 因此再打印一遍最后的情况即可！
	 */
	for (int i=cur; i<a.size(); i++) {
		flag[i] = true;
		combination(a, i+1);
		flag[i] = false;
	}
	for (int i=0; i<a.size(); i++) {
		if (flag[i])
			cout << a[i] << " ";
	}
	cout << endl;
	return;
}

int main()
{
	int arr[6] = {1, 3, 4, 5, 6};
	memset(flag, 0, sizeof(flag));
	vector<int> ret(arr, arr+4);
	vector<int> result;
	combination(ret, 0);
	cout << "================================" << endl;
	for (int i=1; i<(1<<4); i++) {
		for (int j=0, t=i; j<4; j++) {
			if (t & 1) {
				cout << ret[j] << " ";
			}
			t >>= 1;
		}
		cout << endl;
	}
	return 0;
}
