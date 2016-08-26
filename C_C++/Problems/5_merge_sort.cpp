#include <iostream>
#include <cstring>
using namespace std;

/* a,b谁做比较的数组，谁做结果数组，根据传入的判断，顺序是无所谓的 */
void merge(int* a, int* b, int left, int right)
{
	if (left == right)
		return;

	int mid = (left+right) >> 1;
	merge(b, a, left, mid);
	merge(b, a, mid+1, right);
	
	int i = left;
	int j = mid+1;
	int r = left;
	while (i<=mid && j<=right) {
		if (a[i] > a[j])
			b[r++] = a[j++];
		else
			b[r++] = a[i++];
	}

	while (i<=mid)
		b[r++] = a[i++];
	
	while (j<=right)
		b[r++] = a[j++];

}

int main()
{
	int arr[9] = {1, 22, 38, 4, 4, 16, 72, 8, 45};
	int brr[9];
	int size = 9;
	memcpy(brr, arr, sizeof(arr));
	merge(arr, brr, 0, size-1);
	for (int i=0; i<size; i++)
		cout << brr[i] << " ";
	cout << endl;
	return 0;
}


