/*
   现有一个n个整数的序列，你要做的就是交换两个数的位置直到整个序列按照升序排列，那么将这个整数序列排好序，需要交换多少次？例如，1，2，3，5，4，我们只需要交换一次，即将5和4交换即可。
 */
/*
	想要进行交换，用两个vector，一个保存原始数据顺序，一个用来寻找最大或者最小值，
	每次选择一个位置，然后从后向前交换，得到交换次序，知道最后完成n个数据的排序。
	不要小看任何一个题，但也不能妄自菲薄！
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> data(n);
	for(int i=0; i<n; i++)
		cin >> data[i];
	vector<int> tmp(data.begin(), data.end());
	sort(tmp.begin(), tmp.end());
	int swapt = 0;
	int set = 0;
	while(set < n)
	{
		for(int i=0; i<n; i++)
		{
			vector<int>::iterator it = find(data.begin(), data.end(), tmp[i]);
			int pos = it - data.begin();
			for(int j=pos; j>i; j--)
			{
				swap(data[j], data[j-1]);
				swapt ++;
			}
			set ++;
		}
	}
	cout << swapt << endl;
	return 0;
}
