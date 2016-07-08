#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n;
	unsigned int nr[3000];
	while(cin>>n)
	{
		memset(nr, 0, sizeof(nr));
		for(int i=0; i<n; i++)
		{
			cin >> nr[i];
			if(nr[i] % 2 == 0)
			{
				unsigned int tmp = nr[i];
				int bit = 0;
				if(tmp > (1 << 16))
					bit = 32;
				else if(tmp > (1 << 8))
					bit = 16;
				else if(tmp > (1 << 4))
					bit = 8;
				else if(tmp > (1 << 2))
					bit = 4;
				else if(tmp > (1 << 1))
					bit = 2;
				tmp = ((tmp >> 1) & 0x55555555) | ((tmp << 1) & 0xaaaaaaaa);
				tmp = ((tmp >> 2) & 0x33333333) | ((tmp << 2) & 0xcccccccc);
				tmp = ((tmp >> 4) & 0x0f0f0f0f) | ((tmp << 4) & 0xf0f0f0f0);
				tmp = ((tmp >> 8) & 0x00ff00ff) | ((tmp << 8) & 0xff00ff00);
				tmp = ((tmp >> 16) & 0x0000ffff) | ((tmp << 16) & 0xffff0000);
				tmp = tmp >> (32 - bit);
				while(!(tmp & 1))
				{
					tmp = tmp >> 1;
				}
				cout << tmp << " ";
			}
			else
				cout << nr[i] << " ";
		}
		cout << endl;
	}
}
/*
 * 
 * 
 *  int flipNum(int x){
 *   if (x & 1) return x;
 *   int n = 0;
 *   while (x){
 *       n = (n << 1) | (x & 1);
 *       x = x >> 1;
 *   }
 *   return n;
 * }
 */
