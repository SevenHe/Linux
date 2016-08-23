#include <iostream>
using namespace std;

void selection(int* a, int size) {
	for (int i=0; i<size-1; i++) {
		int max = i;
		for (int j=i+1; j<size; j++) {
			if (a[j] > a[max])
				max = j;
		}
		a[i] = a[i] + a[max] - (a[max] = a[i]);
	}
}

int main()
{
	int arr[9] = {1, 22, 38, 4, 4, 16, 72, 8, 45};
	int size = 9;
	selection(arr, 9);
	for (int i=0; i<size; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}
