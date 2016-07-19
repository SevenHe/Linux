#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include <stdio.h>

int main()
{
	unsigned int n, l;
	while(cin >> n >> l)
	{
		vector<int> a(n);
		for(int i=0; i<n; i++)
			cin >> a[i];
		sort(a.begin(), a.end());
		float max_length = a[0] > (l-a[n-1]) ? a[0] : (l-a[n-1]);
		cout << "start: " << max_length << endl;
		bool has_found = false;
		for(int i=1; i<n; i++)
		{
			int m = max_length;
			if(a[i]-a[i-1] > m*2)
			{
				max_length = a[i] - a[i-1];
				cout << a[i] << " - " << a[i-1] << endl;
				has_found = true;
			}
		}
		if(has_found)
			printf("%.2f\n", max_length/2);
		else
			printf("%.2f\n", max_length);
	}


	return 0;
}
