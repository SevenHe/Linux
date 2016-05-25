#include <stdio.h>
#include <stdint.h>

#include <iostream>
#include <vector>
#include <tr1/unordered_map>
using namespace std;

#define bool uint16_t
#define true 1
#define false 0

/*
 *
 *	If you want to use hash_xxx, must use tr1 namespace, and the iterator has been changed to 
 *	const_iterator!!!
 *
 *
 */
int main()
{
	int n = 15;
	int a[n] = {1, 2, 3, 3, 3, 3, 4, 5, 3, 6, 4, 4, 3, 3, 3};
	bool found = false;
	/* strict condition: other numbers are different with each other */
	for(int i=0; i<n/2; i+=2)
	{
		if(a[i] == a[i+1])
		{
			found = true;
			printf("The num is %d\n", a[i]);
			break;
		}
	}
	if(!found && n % 2 == 1)
	{
		printf("The num is %d\n", a[n-1]);
	}
	/* non-strict condition: numbers are whatever you like */
	tr1::unordered_map<int, int> count;
	for(int i=0; i<n; i++)
	{
		if(count.find(a[i]) != count.end())
			count[a[i]] ++;
		else
			count[a[i]] = 1;
	}

	tr1::unordered_map<int, int>::const_iterator it = count.begin();
	//vector<int> keys = count.enum_keys();
	while(it != count.end())
	{
		if(it->second > n/2)
		{
			printf("The num is %d\n", it->first);
			break;
		}
		it ++;
	}
	/* Another way is to use the space to get the time, a two-dimension array to do mappings */
	return 0;
}
