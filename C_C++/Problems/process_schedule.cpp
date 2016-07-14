/*
短作业优先（SJF, Shortest Job First）又称为“短进程优先”SPN(Shortest Process Next)；是对FCFS算法的改进，其目标是减少平均周转时间。
短作业优先调度算法基于这样一种思想：
运行时间短的优先调度；
如果运行时间相同则调度最先发起请求的进程。
等待时间：一个进程从发起请求到开始执行的时间间隔。
现在有n个进程请求cpu，每个进程用一个二元组表示：(p,q),p代表该进程发起请求的时间，p代表需要占用cpu的时间。
请计算n个进程的平均等待时间。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

int cmp(const pair<int, int>& x, const pair<int, int>& y)
{
	if(x.second != y.second)
		return x.second < y.second;
	else
		return x.first < y.first;
}

int main()
{
	int n;
	while(cin >> n)
	{
		int p;
		int q;
		int index = 0;
		vector<pair<int, int> > schedule_order;
		while(n--)
		{
			cin >> p >> q;
			schedule_order.push_back(make_pair(p, q));
		}
		int cur_time = 0;
		float cost = 0.0;
		sort(schedule_order.begin(), schedule_order.end(), cmp);
		for(vector<pair<int, int> >::iterator it = schedule_order.begin();
					it != schedule_order.end(); it++)
		{
			if(it == schedule_order.begin())
				cur_time = (*it).first+(*it).second;
			else
			{
				cost += cur_time - (*it).first;
				cur_time += (*it).second;
			}
		}
		printf("%.4f\n", cost/(schedule_order.size()));
	}

	return 0;
}

