/*
   给定一个长度为N的数组，找出一个最长的单调自增子序列（不一定连续，但是顺序不能乱）
   例如：给定一个长度为8的数组A{1,3,5,2,4,6,7,8}，则其最长的单调递增子序列为{1,2,4,6,7,8}，长度为6.
 */
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;
int seq[3000];
map<int, int> reback;

int find_root(int t)
{
	int maxV_index = 0;
	int maxV = 0;
	for(int i=0; i<t; i++)
	{
		if(arr[i] < arr[t])
		{
			if(seq[i] > maxV)
			{
				maxV = seq[i];
				maxV_index = i;
			}
		}
	}
	if(maxV != 0)
		reback[t] = maxV_index;
	else
		reback[t] = t;
	return maxV;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		arr.clear();
		reback.clear();
		memset(seq, 0, sizeof(seq));
		int N;
		cin >> N;
		while(N--)
		{
			int nr;
			cin >> nr;
			arr.push_back(nr);
		}
		seq[0] = 1;
		reback[0] = 0;
		for(int i=1; i<arr.size(); i++)
		{
			int rootV = find_root(i);
			if(rootV != 0)
				seq[i] = rootV + 1;
			else
				seq[i] = 1;
		}
		int index = 0;
		int max = 0;
		for(int i=0; i<arr.size(); i++)
		{
			if(seq[i] > max)
			{
				max = seq[i];
				index = i;
			}
		}
		vector<int> tmp;
		while(reback[index] != index)
		{
			tmp.push_back(arr[index]);
			index = reback[index];
		}
		tmp.push_back(arr[index]);
		reverse(tmp.begin(), tmp.end());
		for(int i=0; i<tmp.size(); i++)
			cout << tmp[i] << " ";
		cout << endl;
	}
	return 0;
}


