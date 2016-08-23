#include <iostream>
#include <vector>
using namespace std;

bool flag[10] = {0};

void permutation(vector<int>& a, int cur, vector<int>& ret)
{
	if (cur == a.size()) {
		for (int i=0; i<a.size(); i++) {
			if (flag[i])
				cout << ret[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i=0; i<a.size(); i++) {
		if (!flag[i]) {
			flag[i] = true;
			ret.push_back(a[i]);
			permutation(a, cur+1, ret);
			ret.pop_back();
			flag[i] = false;
		}
	}
	return;
}

int main()
{
	int arr[4] = {1, 4, 5, 6};
	vector<int> a(arr, arr+4);
	vector<int> ret;
	permutation(a, 0, ret);
	return 0;
}
