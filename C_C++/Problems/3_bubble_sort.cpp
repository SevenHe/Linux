#include <iostream>
using namespace std;

void bubble(int* a, int size)
{
	for (int i=0; i<size-1; i++) {
		for (int j=i+1; j<size; j++) {
			if (a[i] > a[j])
				a[j] = a[i] + a[j] - (a[i] = a[j]);
		}
	}
}

int main()
{
	int arr[9] = {1, 22, 38, 4, 4, 16, 72, 8, 45};
	int size = 9;
	bubble(arr, size);
	for (int i=0; i<size; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}
