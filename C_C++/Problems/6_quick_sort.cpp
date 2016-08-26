#include <iostream>
using namespace std;

void quick_sort(int* a, int left, int right)
{
	if (left >= right)
		return;

	int key = a[left];
	int i = left;
	int j = right;

	/* 由于相等情况，key仍然要继续向前或者向后，以处理所有情况，
	 * 因此可能相等元素顺序改变，则为不稳定排序 
	 */
	while (i < j) {
		/* 必须有等于，用于处理相同的元素 */
		while (a[j] >= key && j > i) j--;
		/* 跳出条件,j=i,所以这句赋值没有副作用 */
		a[i] = a[j];
		while (a[i] <= key && i < j) i++;
		a[j] = a[i];
	}
	a[i] = key;
	
	quick_sort(a, left, i-1);
	quick_sort(a, i+1, right);
}

int main()
{
	int arr[9] = {1, 22, 38, 4, 4, 16, 72, 8, 45};
	int size = 9;
	quick_sort(arr, 0, size-1);
	for (int i=0; i<size; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}
