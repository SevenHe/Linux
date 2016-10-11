#include <iostream>
using namespace std;

void heap_sort(int* a, int size, int cur)
{
	int left = cur*2+1;
	int right = cur*2+2;
	int maxval = cur;
	if (left < size && a[left] < a[cur]) {
		a[cur] = a[cur] + a[left] - (a[left] = a[cur]);
		maxval = left;
	}
	if (right < size && a[right] < a[cur]) {
		a[cur] = a[cur] + a[right] - (a[right] = a[cur]);
		maxval = right;
	}
	if (maxval != cur) {
		heap_sort(a, size, maxval);
	}
}

void build_heap(int* a, int size)
{
	int last = size/2 - 1;
	for (int i=last; i>=0; i--)
		heap_sort(a, size, i);
}

void print_array(int *a, int size)
{
	cout << endl << "---->>";
	for (int i=0; i<size; i++)
		cout << a[i] << " ";
	cout << endl;
}

int pop_heap(int* a, int size)
{
	a[size-1] = a[0] + a[size-1] - (a[0] = a[size-1]);
	return a[size-1];
}

int main()
{
	int arr[9] = {1, 22, 38, 4, 4, 16, 72, 8, 45};
	int size = 9;
	build_heap(arr, size);
	print_array(arr, size);
	for (int i=0; i<size; i++) {
		int val = pop_heap(arr, size-i);
		cout << val << " ";
		build_heap(arr, size-i-1);
		print_array(arr, size-i-1);
	}
	cout << endl;
	return 0;
}
