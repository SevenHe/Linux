#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<int, vector<int> > sodier;
int count = 0;
int size = 0;

void perm_next(int index, int selection[])
{
	if(index >= size)
	{
		count ++;
		return;
	}
	else
	{
		for(vector<int>::iterator it = sodier[index].begin();
				it != sodier[index].end(); it++)
		{
			//cout << index << ": " << *it << endl;
			int selection2[6];
			memcpy(selection2, selection, sizeof(int)*6);
			if(selection2[*it] == -1)
			{
				selection2[*it] = index;
			//	cout << index << " select: " << *it << endl;
				perm_next(index+1, selection2);
			}
			//else
			//	cout << "selection error:" << *it << "," << selection2[*it] << endl;
		}
	}
}

int main()
{
	int n;
	while(cin >> n)
	{
		sodier.clear();
		size = n;
		count = 0;
		int id = 0;
		string s;
		while(n--)
		{
			cin >> s;
			int len = s.size();
			for(int i=0; i<len; i++)
				sodier[id].push_back((int)(s[i]-'0'));
			id ++;
		}
		int selection[6];
		memset(selection, -1, sizeof(selection));

		perm_next(0, selection);
		cout << count << endl;
	}
	return 0;
}
