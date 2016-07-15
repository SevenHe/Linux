/*
 * 小萌是个WOW发烧友，每天都痴迷于他的法师号。精诚所至金石为开，小萌穿越到WOW的世界中了...
 初 来乍到的小萌在暴风城的小巷中，遇见了一位善良的德鲁伊。德鲁伊听了小萌的故事，打算帮助他在WOW这个世界好*好活下去，于是，把自己的东西都给了小萌了...
 德鲁伊的东西太多了，于是小萌去拍卖行买了几个包裹，一切妥当之后，小萌开始把东西装进包裹里。
 不过，因为小萌穿越时候脑袋先着地，所以脑子不好用，每次他拿起一个物品，要不装进包里，要不就直接扔掉...
 而且，一个背包一旦不往里装东西，小萌就会封上口不再用...
 现在，告诉你小萌每个物品的体积，背包的个数和容量，以及小萌拿物品的顺序，你要帮助小萌求出他能拿走多少东西。
 *
 按顺序，且背包不能被撑爆！
 */
/*
 *   给定一个长度为N的数组，找出一个最长的单调自增子序列（不一定连续，但是顺序不能乱）
 *   例如：给定一个长度为8的数组A{1,3,5,2,4,6,7,8}，则其最长的单调递增子序列为{1,2,4,6,7,8}，长度为6.
 */
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int get(vector<int> goods, int cur_content, int content, int rest_nr, int nr, int choice)
{
	if(rest_nr == 0 && cur_content == 0)
		return nr;
	if(goods.size() == 0)
		return nr;
	vector<int> next(goods.begin()+1, goods.end());
	int cur_good = goods[0];
	if(choice == 0)
	{
		cout << "not choose:" << cur_good << endl;
		return max(get(next, cur_content, content, rest_nr, nr, 0), 
				get(next, cur_content, content, rest_nr, nr, 1));
	}
	else if(choice == 1)
	{
		cout << "choose:" << cur_good << endl;
		if(cur_content < cur_good && cur_good < content)
		{
			cur_content = content - cur_good;
			if(rest_nr > 0)
			{
				rest_nr --;
				nr ++;
			}
		}
		else if(cur_content >= cur_good)
		{
			cur_content = cur_content - cur_good;
			if(cur_content == 0 && rest_nr == 0)
				return nr+1;
			else
				nr ++;
		}

		cout << "current:" << cur_content << "," << rest_nr << endl;
		return max(get(next, cur_content, content, rest_nr, nr, 0),
				get(next, cur_content, content, rest_nr, nr, 1));
	}
	return -1;	
}

int main()
{
    int R;
    cin >> R;
    while(R--)
    {
		vector<int> arr;
		vector<int> chip;
        int N,T,M;
        cin >> N >> T >> M;
        while(N--)
        {
            int nr;
            cin >> nr;
            arr.push_back(nr);
        }
		int ret = max(get(arr, T, T, M-1, 0, 0), get(arr, T, T, M-1, 0, 1));
		cout << ret << endl;
    }
    return 0;
}


