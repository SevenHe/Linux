/*
   Arthur最近搬到了新的别墅，别墅特别大，原先的桌子显得比较小，所以他决定换一张新的桌子。他买了一张特别大的桌子，桌子是由很多条桌腿进行支撑的，可是回到家之后他发现桌子不稳，原来是桌子腿长度不太相同。他想要自己把桌子修理好，所以他决定移除掉一些桌腿来让桌子变得平稳。桌子腿总共有n条腿，第i条腿长度为li，Arthur移除第i桌腿要花费代价为di。假设k条腿桌子平稳的条件:超过一半桌腿能够达到桌腿长度的最大值。例如：一条腿的桌子是平稳的，两条腿的桌子腿一样长时是平稳的。请你帮Arthur计算一下是桌子变平稳的最小总代价。 
 */
/*
 * 注意，解读题目的重点，重点就是桌腿长，有三种情况，大于当前的，小于当前的，等于当前的，然后实现逻辑即可！
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include <limits.h>

int main()
{
	int n;
	cin >> n;
	vector<int> l(n);
	vector<int> d(n);
	int flag[106] = {0};
	for(int i=0; i<n; i++)
		cin >> l[i];
	for(int i=0; i<n; i++)
		cin >> d[i];
	int cost = INT_MAX;
	for(int i=0; i<n; i++)
	{
		if(flag[l[i]])
			continue;
		int maxl = l[i];
		flag[106] = 1;
		vector<int> value;
		int eq_nr = 0;
		int tmp = 0;
		for(int j=0; j<n; j++)
		{
			if(l[j] == maxl)
				eq_nr ++;
			else if(l[j] < maxl)
				value.push_back(d[j]);
			else if(l[j] > maxl)
				tmp += d[j];
		}
		if(eq_nr > value.size())
			cost = cost > tmp ? tmp : cost;
		else
		{
			sort(value.begin(), value.end());
			for(int k=0; k<value.size()-eq_nr+1; k++)
				tmp += value[k];
			cost = cost > tmp ? tmp : cost;
		}
	}
	cout << cost << endl;
	return 0;
}
