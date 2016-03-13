#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	int a[3] = {10, 9, 8};
	int* b = new int[3];

	memcpy(b, a, sizeof(int)*3);
	
	for(int i=0; i<3; i++)
		cout << "b[" << i <<  "]: " << b[i] << endl;

	delete b;

	return 0;
}	
