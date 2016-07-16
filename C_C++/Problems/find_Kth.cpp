/*
   有一个整数数组，请你根据快速排序的思路，找出数组中第K大的数。
   给定一个整数数组a,同时给定它的大小n和要找的K(K在1到n之间)，请返回第K大的数，保证答案存在。
 */
/*
 * 快速排序的划分思路，从一个点来判断大小，不必交换数组中的位置，只需前后i和j交换值，最后再将key赋值给i即可！！
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Finder {
	public:
		int MK;
		int MN;
		int partition(vector<int> a, int low, int high)
		{
			if(low == high)
				return a[low];
			int key = a[low];
			int i = low;
			int j = high;
			while(i < j)
			{
				while(a[j] > key && j > i) j--;
				if(i < j)
					a[i] = a[j];
				while(a[i] < key && i < j) i++;
				if(i < j)
					a[j] = a[i];
			}
			a[i] = key;
			cout << "##  key = " << key << ", lh: " << low << ", " << high << endl;
			cout << "a[i]:" << a[i] << endl;
			for(int k=0; k<MN; k++)
				cout << a[k] << " ";
			cout << endl;
			if(MN - i == MK)
				return key;
			else if(MN - i > MK)
				return partition(a, i+1, high);
			else
				return partition(a, low, i-1);
		}
		int findKth(vector<int> a, int n, int K) {
			MK = K;
			MN = n;
			return partition(a, 0, n-1);
		}
};

int main()
{
	int a[] = {1, 4, 7, 8, 19, 23, 3, 5, 6, 34, 16, 9};
	vector<int> t(a, a+sizeof(a)/sizeof(int));

	Finder f;
	cout << "Find :" << f.findKth(t, sizeof(a)/sizeof(int), 5);
	return 0;
}
