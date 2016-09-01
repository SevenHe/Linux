#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/* 组合，用nr记录选择个数，结果是求某个个数的结果的集合 */
/* 而求集合，只需要一个cur，指示是否选择到了数组的结尾，
结果是数组选到结尾，所有的true or false的情况都已经被选到
*/

bool flag[10] = {0};

void combination(vector<int>& a, vector<int>& ret, int cur, int nr)
{
	if (cur == a.size())
		return;
	/* 这种方法要修复所有cur后都为false的情况，因此，最好的求集合的方法，就是在循环中，每加入一个解
	 * 就记录一次！！！
	if (cur == a.size()) {
		for (int i=0; i<ret.size(); i++)
			cout << ret[i] << " ";
		cout << endl;
		return;
	}
	*/
	/*
	if (nr == 2) {
		for (int i=0; i<a.size(); i++) {
			if (flag[i])
				cout << a[i] << " ";
		}
		cout << endl;
		return;
	}
	// C(m,n)
	else if (nr > 2)
		return;
	*/
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
	// 用额外的空间和flag的方法一样，看题目需求，但是flag方法节省空间和时间！
	for (int i=cur; i<a.size(); i++) {
		ret.push_back(a[i]);
		// 这种方法，求集合的思路简单易理解，每次有一个解就输出，不会出现重复选择的情况
		// 唯一的问题是，该方法求的是真子集，没有空集合，若有需求要自己加入！
		for (int j=0; j<ret.size(); j++)
			cout << ret[j] << " ";
		cout << endl;
		//flag[i] = true;
		combination(a, ret, i+1, nr+1);
		//flag[i] = false;
		ret.pop_back();
	}
	/* 求集合的一种方法需要此循环，修复都没选的情况！
	for (int i=0; i<a.size(); i++) {
		if (flag[i])
			cout << a[i] << " ";
	}
	cout << endl;
	*/
	return;
}

int main()
{
	int arr[6] = {1, 3, 4, 5, 6};
	memset(flag, 0, sizeof(flag));
	vector<int> ret(arr, arr+4);
	vector<int> result;
	combination(ret, result, 0, 0);
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
