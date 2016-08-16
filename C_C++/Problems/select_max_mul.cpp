/*
   有 n 个学生站成一排，每个学生有一个能力值，牛牛想从这 n 个学生中按照顺序选取 k 名学生，要求相邻两个学生的位置编号的差不超过 d，使得这 k 个学生的能力值的乘积最大，你能返回最大的乘积吗？ 
 */
/*
当每个选择之间的差距大于等于数组长度时，相当于排序，取最大值相乘;
否则，从一个点开始，按照间距d，每次在间距中取最大的k-(size-d)(>0)个数,或(<0)一般取一个数，即可通过.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

/*
   long long dfs(vector<int>& a, int cur, long long mul, int k, int& d)
   {
   if (k == 0 || a.size()-cur < k) {
   return mul;
   }
   long long max = 0;
   for (int i=cur; i<a.size(); i++) {
   if (i-cur <= d) {
   long long tmp1 = dfs(a, i+1, mul*a[i], k-1, d);
   if (tmp1 > max)
   max = tmp1;
   }
   if (a.size()-i-1 < k)
   break;
   long long tmp2 = dfs(a, i+1, mul, k, d);
   if (tmp2 > max)
   max = tmp2;
   }
   return max;
   }
 */

int main()
{
	int n;
	while (cin >> n) {
		vector<int> a(n);
		int k, d;
		for (int i=0; i<n; i++)
			cin >> a[i];
		cin >> k >> d;
		long long ret = 0;
		for (int i=0; i<=n-k; i++) {
			// to avoid repeating by using a bool array!
			vector<bool> flag(n, false);
			flag[i] = true;
			long long mul = a[i];
			int nr = k-1;
			for (int j=i+1; nr>0;) {
				long long tmp = mul;
				int last_max = j;
				for (int t=j; t-last_max<=d && a.size()-t>=nr && t<j+d; t++) {
					if (flag[t])
						continue;
					if (abs(mul*a[t]) > abs(tmp)) {
						tmp = mul*a[t];
						j = t;
					}
				}
				cout << "Select: " << j << "-" << a[j] << endl;
				flag[j] = true;
				mul = tmp;
				nr--;
				if (d >= a.size())
					j = i+1;
				else
					j++;
			}
			cout << "GET: " << mul << endl;
			if (mul > ret)
				ret = mul;
		}
		cout << ret << endl;
	}
	return 0;
}
