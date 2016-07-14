/*
	Sunday算法，在实现算法的过程中，遇到了循环套反复循环的问题，花了很多时间
	以后再思索循环嵌套循环的情况，先要把状态的完整转移过程想清楚，然后合理分配循环节
	大循环可以放在主函数，小循环可以放在子函数中，过程一定要想清楚。

	PS：另外该Sunday算法，可以用动态规划的思想去解决，但是在回溯的过程中，动态规划的数组要得到重置，
	并不比这个方法简单太多。
*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include <time.h>
#include <stdio.h>

typedef int (*func)(string, string);

/* 
	返回值极其有用的函数，不要让返回值出现太多的情况利用，尤其是正负，会导致整个逻辑的混乱，
	最好是只有一面是有用的，在主函数中稍加判断即可，多一些变量，可以减少很多逻辑。
*/
int find_prev_pos(int from, string ptn, char p)
{
	for(int i=from; i>=0; i--)
	{
		if(p == ptn[i])
			return i;
	}
	return -1;
}

/* 两个字符串匹配，不仅要考虑主要字符串，还要考虑p字符串是否越界 */
int match(string r, string p, int rfrom)
{
	int pi = 0;
	for(int i=rfrom; i<r.size(); i++)
	{
		if(r[i] == p[pi])
		{
			pi++;
			if(pi == p.size())
				break;
		}
		else
			return -rfrom-1;
	}
	return rfrom;
}

/* To be optimized for"aaaaaaaaaaaaadcaaaaaa, aaaaaaab" */
int Sunday(string raw, string ptn)
{
	cout << "#####Sunday#####" << endl;
	int len = raw.size();
	int plen = ptn.size();
	int ret = -1;
	int pos = 0;
	int i = 0;
	while(i < len)
	{
		pos = match(raw, ptn, i);	
//		cout << "match1 from " << i << " to " << pos << endl;
		if(pos < 0)
		{
			pos = abs(pos+1);
			if(pos + plen >= raw.size())
			{
				ret = -1;
				break;
			}
			int ppos = plen - 1;
			char rs = raw[pos+plen];
			bool has_found = false;
			int tmp = 0;
			while((ppos = find_prev_pos(ppos, ptn, rs)) != -1)
			{
				has_found = true;
				tmp = match(raw, ptn, pos+plen-ppos);
//		cout << "match2 from " << pos+plen-ppos << " to " << tmp << endl;
				if(tmp< 0)
				{
					ppos--;
					tmp = abs(tmp+1);
					if(find_prev_pos(ppos, ptn, rs) == -1)
					{
						pos = tmp;
						rs = raw[pos+plen];
						ppos = plen - 1;
					}
					continue;
				}
				else
				{
					ret = tmp;
					return ret;
				}
			}
			if(has_found)
			{
				pos = tmp;
				i = pos + plen;
			}
			else
				i = pos + plen + 1;
			continue;
		}
		else
		{
			ret = i;
			break;
		}
	}
	return ret;
}

int lib_find(string raw, string ptn)
{
	cout << "#####string_lib_find#####" << endl;
	int ret = raw.find(ptn);
	if(ret > raw.size())
		return -1;
	return ret;
}

void time_wrapper(func f, string s1, string s2)
{
	int pos = 0;
	clock_t start, end;
	start = clock();
	pos = f(s1, s2);
	if(pos != -1)
	{
		cout << s1 << endl;
		for(int i=0; i<pos; i++)
			cout << " ";
		cout << s2 << endl;
	}
	else
		cout << "Match error!" << endl;
	end = clock();
	printf("Elapsed time: %.4fms\n", (double)(end-start)*1000/CLOCKS_PER_SEC);
}

int main()
{
	string raw;
	string ptn;
	while(cin >> raw >> ptn)
	{
		time_wrapper(Sunday, raw, ptn);
		time_wrapper(lib_find, raw, ptn);
	}

	return 0;
}
