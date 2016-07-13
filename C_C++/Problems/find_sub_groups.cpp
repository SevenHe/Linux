#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int cmp(const pair<int, int>& x, const pair<int, int>& y)
{
	return x.first < y.first;
}

int cal(int x)
{
	if(x < 2)
		return 0;
	else if(x == 2)
		return 1;
	else
		return x*(x-1)/2;
}

int main()
{
	int N;
	while(cin >> N)
	{
		map<int, int> count;
		int find0 = 0;
		while(N--)
		{
			int nr;
			cin >> nr;
			count[nr] ++;
            /* 每个数都是不一样的，即使值相同，也要进行两两分组！！！ */
			if(count[nr] >= 2)
			{
				find0 -= cal(count[nr]-1);
				find0 += cal(count[nr]);
			}
		}

		map<int, int>::iterator min = count.begin();
		map<int, int>::iterator max = --count.end();
		if(find0)
			cout << find0 << " ";
		else
		{
			vector<pair<int, int> > data;
			for(map<int, int>::iterator it = count.begin(); it != count.end(); it++)
				data.push_back(make_pair(it->first, it->second));
			sort(data.begin(), data.end(), cmp);
			// may be 3,4,5,6
			int minV, minL, minR;
			int C = 0;
			minV = max->first - min->first;
			for(int i=0; i<data.size()-1; i++)
			{
				if(data[i+1].first - data[i].first < minV)
				{
					C = 0;
					minV = data[i+1].first - data[i].first;	
					minL = i;
					minR = i + 1;
					C = data[minR].second * data[minL].second;
				}
				else if(data[i+1].first - data[i].first == minV)
					C += data[i+1].second * data[i].second;
				cout << data[i].first << "," << data[i].second << " ";
			}
			cout << endl;
			cout << C << " ";
		}
		cout << abs(max->second * min->second) << endl;
	}

	return 0;
}


