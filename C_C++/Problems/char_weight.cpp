/*
有 n 个字符串，每个字符串都是由 A-J 的大写字符构成。现在你将每个字符映射为一个 0-9 的数字，不同字符映射为不同的数字。这样每个字符串就可以看做一个整数，唯一的要求是这些整数必须是正整数且它们的字符串不能有前导零。现在问你怎样映射字符才能使得这些字符串表示的整数之和最大？

    求多个字符串或类似结构怎么组合出最大的权重，利用每个元素在该位置上的假设权值相加，得到总占比，然后排序分配即可！
    比如利用十进制，第二位上为10，第三位上为100等等。
    其中一个最重要的问题就是数字很多很大时，很容易超出int表示的范围，因此要有一个预警，会不会导致溢出。
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int cmp(const pair<char, unsigned long>& x, const pair<char, unsigned long>& y)
{
	return x.second < y.second;
}

int main()
{
	int n;
	cin >> n;
	vector<string> str(n);
	map<char, unsigned long> weight;
	vector<pair<char, unsigned long> > ordered_weight;
	set<char> first_cr;
	for(int i=0; i<n; i++)
	{
		cin >> str[i];
		first_cr.insert(str[i][0]);
		unsigned long tw = 1;
		for(int j=str[i].size()-1; j>=0; j--)
		{
			weight[str[i][j]] += tw;
			tw *= 10;
		}
	}
	for(map<char, unsigned long>::iterator it = weight.begin(); it != weight.end(); it++)
		ordered_weight.push_back(make_pair(it->first, it->second));
	sort(ordered_weight.begin(), ordered_weight.end(), cmp);
    /* 前导不为0,找到不占据首位位置，并且总权重最小的字符，放在0处代替（假如有10种字符） */
	int pos = -1;
	for(int i=0; i<ordered_weight.size(); i++)
	{
		if(first_cr.find(ordered_weight[i].first) == first_cr.end())
		{
			pos = i;
			break;
		}
	}
	if(pos != -1)
	{
		pair<char, unsigned long> val = ordered_weight[pos];
		for(int i=pos; i>0; i--)
			ordered_weight[i] = ordered_weight[i-1];
		ordered_weight[0] = val;
	}
	//for(int i=0; i<ordered_weight.size(); i++)
	//	cout << ordered_weight[i].first << ":" << ordered_weight[i].second << endl;
    unsigned long sum = 0;
	int value[11];
	int maxi = ordered_weight.size();
	for(int i=maxi-1, ve=9; i>=0; i--, ve--)
	{
		value[ordered_weight[i].first - 'A'] = ve;
		//cout << ordered_weight[i].first << ":" << ve << endl;
	}

	for(int i=0; i<n; i++)
	{
		int tmpl = str[i].size();
		unsigned long tmpb = 1;
		for(int j=tmpl-1; j>=0; j--)
		{
            unsigned long tt = value[str[i][j]-'A']*tmpb;
			sum += tt;
			//cout << "get:" << str[i][j] << "," << value[str[i][j]-'A'] << "," << tmpb << endl;
			//cout << sum << "+" << tt << endl;;
			tmpb *= 10;
		}
		cout << "cur_sum:" << sum << endl;
	}
	cout << sum << endl;
	return 0;
}

		
