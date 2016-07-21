/*
   搜狐员工小王最近利用假期在外地旅游，在某个小镇碰到一个马戏团表演，精彩的表演结束后发现团长正和大伙在帐篷前激烈讨论，小王打听了下了解到， 马戏团正打算出一个新节目“最高罗汉塔”，即马戏团员叠罗汉表演。考虑到安全因素，要求叠罗汉过程中，站在某个人肩上的人应该既比自己矮又比自己瘦，或相等。 团长想要本次节目中的罗汉塔叠的最高，由于人数众多，正在头疼如何安排人员的问题。小王觉得这个问题很简单，于是统计了参与最高罗汉塔表演的所有团员的身高体重，并且很快找到叠最高罗汉塔的人员序列。 现在你手上也拿到了这样一份身高体重表，请找出可以叠出的最高罗汉塔的高度，这份表中马戏团员依次编号为1到N。
 */
/*
 * 跟自己一样高可以,但必须要比自己瘦.
 * 不清楚的条件,写完框架,进行调试.
 * 下一个人的状态要用到上一个人的状态,动态规划是很好的选择.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

map<int, int> reback;
int cmp1(const pair<int, int>& x, const pair<int, int>& y)
{
	if(x.first != y.first)
		return x.first > y.first;
	return x.second > y.second;
}

int findPrev(vector<pair<int, int> >& member, vector<int>& nr, int cur)
{
	int len = member.size();
	int ret = cur;
	int maxnr = 0;
	for(int i=0; i<cur; i++)
	{
		if(member[i].first > member[cur].first &&
			member[i].second >= member[cur].second)
		{
			if(nr[i] > maxnr)
			{
				maxnr = nr[i];
				ret = i;
			}
		}
	}
	reback[cur] = ret;
	return ret;
}


int main()
{
	int N;
	while(cin >> N)
	{
		vector<pair<int, int> > member(N);
		vector<int> nr(N);
		for(int i=0; i<N; i++)
		{
			int nr, wt, ht;
			cin >> nr >> wt >> ht;
			member[i] = make_pair(wt, ht);
		}
		sort(member.begin(), member.end(), cmp1);
		for(int i=0; i<N; i++)
		{
			int prev = findPrev(member, nr, i);
			if(i == prev)
				nr[i] = 1;
			else
				nr[i] = nr[prev] + 1;
		}
		int maxV = 0;
        int maxI = 0;
		for(int i=0; i<N; i++)
        {
            if(nr[i] > maxV)
            {
                maxV = nr[i];
                maxI = i;
            }
        }
        while(reback[maxI] != maxI)
        {
            cout << maxI << ", ht:" << member[maxI].second << ", wt:" << member[maxI].first << endl;
            maxI = reback[maxI];
        }
        cout << "maxV: " << maxV << endl;
	}
	return 0;
}
