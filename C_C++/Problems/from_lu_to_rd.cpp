/*
从左上角到右下角，有多少种走法，或者求最大路径值
状态从一点转移到另一点，不必在意中间选的哪点，只要最后的计数
因此选择二维数组，进行计数
*/
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		int arr[50][50];
		memset(arr, 0, sizeof(arr));
		arr[0][1] = 1;
		arr[1][0] = 1;
		for (int i=0; i<=n; i++)
			arr[i][0] = 1;
		for (int i=0; i<=n; i++)
			arr[0][i] = 1;
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=n; j++) {
				arr[i][j] = arr[i-1][j] + arr[i][j-1];
			}
		}
		cout << arr[n][n] << endl;
	}
	return 0;
}
