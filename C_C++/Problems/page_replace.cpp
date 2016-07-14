/*
在计算机中，页式虚拟存储器实现的一个难点是设计页面调度（置换）算法。其中一种实现方式是FIFO算法。
FIFO算法根据页面进入内存的时间先后选择淘汰页面，先进入内存的页面先淘汰，后进入内存的后淘汰。
假设Cache的大小为2,有5个页面请求，分别为 2 1 2 3 1，则Cache的状态转换为：(2)->(2,1)->(2,1)->(1,3)->(1,3)，其中第1,2,4次缺页，总缺页次数为3。
现在给出Cache的大小n和m个页面请求，请算出缺页数。
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	int m;
	while(cin >> n >> m)
	{
		vector<int> cache;
		int count = 0;
		while(m--)
		{
			int nr;
			cin >> nr;
			if(find(cache.begin(), cache.end(), nr) == cache.end())
			{
				if(cache.size() == n)
				{
					cache.erase(cache.begin());
					cache.push_back(nr);
				}
				else if(cache.size() < n)
					cache.push_back(nr);
				count ++;
			}
		}
		cout << count << endl;
	}

	return 0;
}

