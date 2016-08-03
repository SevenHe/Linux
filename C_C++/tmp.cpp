#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include <stdio.h>

/* the p or ptr is just a pointer, point to an array, but the array does not has memory to store data! */
int (*(*p)[10])(int*);
int (*(*ptr)[10]);

int test(int* a)
{
	return 1;
}

int main()
{
	int buf[10] = {1, 2};
	int *bb[10];
	int (*pr)[10];
	pr = &buf;
	(*pr)[2] = 3;
	int a = 2;
	int b = 0;
	cout << "pr=" << (*pr)[2] << endl;
	ptr = &bb;
	(*ptr)[0] = &a;
	cout << "ptr=" << *(*ptr)[0] << endl;
	int (*bbb[10])(int*);
	//bbb[0] = &test;
	p = &bbb;
	(*p)[0] = test;
	b = ((*p)[0])(&a);
	//b = (bbb[0])(&a);
	printf("b=%d\n", b);
	/*
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
	*/

	return 0;
}
