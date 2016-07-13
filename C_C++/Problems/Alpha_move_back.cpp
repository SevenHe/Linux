#include <iostream>
using namespace std;

int main()
{
	string s;
	while(cin >> s)
	{
		/*
		int swapW = len - 1;
		for(int i=len-1; i>=0; i--)
		{
			if(s[i] >= 'A' && s[i] <= 'Z')
			{
				if(i != swapW)
				{
					swap(s[i], s[swapW]);
					swapW--;
				}
				else
					swapW--;
			}
		}
		*/
		int len = s.size();
		for(int i=0; i<len; i++)
			if(s[i] >= 'a' && s[i] <= 'z')
				cout << s[i];
		for(int i=0; i<len; i++)
			if(s[i] >= 'A' && s[i] <= 'Z')
				cout << s[i];
		cout << endl;
	}

	return 0;
}
