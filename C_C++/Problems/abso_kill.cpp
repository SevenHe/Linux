#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int main()
{
	int n;
	while(cin >> n)
	{
		map<string, int> arrange_scroll;
		map<string, int> middle_scroll;
		map<string, int> str_order;
		for(int i=0; i<n; i++)
		{
			string s;
			int nr;
			cin >> s >> nr;
			if(nr == 1)
				middle_scroll[s] = nr;
			else
				arrange_scroll[s] = nr;
		}
		map<string, int>::iterator mip = arrange_scroll.begin();
		while(mip != arrange_scroll.end())
		{
			if(mip == arrange_scroll.begin())
				cout << mip->first;
			else
				cout << " " << mip->first;
			mip->second -= 2;
			str_order[mip->first] = mip->second;
			mip ++;
		}
		arrange_scroll.insert(middle_scroll.begin(), middle_scroll.end());
		mip = arrange_scroll.begin();
		while(mip != arrange_scroll.end())
		{
			while(mip->second > 0)
			{
				cout << " " << mip->first;
				mip->second --;
			}
			mip ++;
		}
		mip = str_order.begin();
		while(mip != str_order.end())
		{
			cout << " " << mip->first;
			mip ++;
		}
		cout << endl;
	}

	return 0;
}
