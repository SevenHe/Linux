#include <iostream>
using namespace std;

void insertion(int* a, int size)
{
	int nil = 0;
	for (int j=nil+1; j<size; j++) {
		if (a[j] >= a[nil])
			nil = j;
		else {
			int tmp = a[j];
			for (int i=j-1; i>=0; i--) {
				if (a[i] > tmp)
					a[i+1] = a[i];
				else {
					a[i+1] = tmp;
					nil = j;
					break;
				}
			}
		}
	}
}

int main()
{
	int arr[9] = {1, 22, 38, 4, 4, 16, 72, 8, 45};
	int size = 9;
	insertion(arr, size);
	for (int i=0; i<size; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}
