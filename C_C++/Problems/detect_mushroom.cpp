/*
在N*M的草地上,提莫种了K个蘑菇,蘑菇爆炸的威力极大,兰博不想贸然去闯,而且蘑菇是隐形的.只 有一种叫做扫描透镜的物品可以扫描出隐形的蘑菇,于是他回了一趟战争学院,买了2个扫描透镜,一个 扫描透镜可以扫描出(3*3)方格中所有的蘑菇,然后兰博就可以清理掉一些隐形的蘑菇. 问:兰博最多可以清理多少个蘑菇?
注意：每个方格被扫描一次只能清除掉一个蘑菇。 
输入描述:
第一行三个整数:N,M,K,(1≤N,M≤20,K≤100),N,M代表了草地的大小;
接下来K行,每行两个整数x,y(1≤x≤N,1≤y≤M).代表(x,y)处提莫种了一个蘑菇.
一个方格可以种无穷个蘑菇.
*/
/*
注意，种蘑菇的时候，利用的坐标系从1开始，因此扫描也一定要从1开始，从0开始，一定会犯错！
二维数组，可以用vector嵌套+循环resize搞定！
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int N, M;
int mushroom[21][21];

int getMushroom(int x, int y, int tmp[21][21], int time)
{
	int ret = 0;
	for(int i=x; i<x+3 && i<N; i++)
	{
		for(int j=y; j<y+3 && j<M; j++)
		{
			if(tmp[i][j] > 0)
			{
				ret ++;
				tmp[i][j] --;
			}
		}
	}
	if(time == 1)
		return ret;
	int max = 0;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			int newArr[21][21];
			memcpy(newArr, tmp, sizeof(newArr));
			int val = getMushroom(i, j, newArr, time+1);
			if(val > max)
				max = val;
		}
	}
	return ret+max; 
}

int main()
{
	int K;
	while(cin >> N >> M >> K)
	{
		memset(mushroom, 0, sizeof(mushroom));
		for(int i=0; i<K; i++)
		{
			int x,y;
			cin >> x >> y;
			mushroom[x][y] ++;
		}
		int count_max = 0;
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<M; j++)
			{
				int newArr[21][21];
				memcpy(newArr, mushroom, sizeof(newArr));
				int tmp = getMushroom(i, j, newArr, 0);
				if(tmp > count_max)
					count_max = tmp;
			}
		}
		cout << count_max << endl;
	}
	return 0;
}
