/*
 狐进行了一次黑客马拉松大赛，全公司一共分为了N个组，每组一个房间排成一排开始比赛，比赛结束后没有公布成绩，但是每个组能够看到自己相邻的两个组里比自己成绩低的组的成绩，比赛结束之后要发奖金，以1w为单位，每个组都至少会发1w的奖金，另外，如果一个组发现自己的奖金没有高于比自己成绩低的组发的奖金，就会不满意，作为比赛的组织方，根据成绩计算出至少需要发多少奖金才能让所有的组满意
 */
/*
 * 考虑状态,因为只有临近的两个组,因此每边有两种状态,总共4个状态放在判断中即可.
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	while(cin >> N)
	{
		vector<int> grade(N);
		vector<int> reward(N, 1);
		for(int i=0; i<N; i++)
			cin >> grade[i];
        if(grade[0] > grade[1])
            reward[0] = 2; 
        cout << reward[0] << "--";
		for(int i=1; i<N-1; i++)
		{
			if(grade[i+1] > grade[i] && grade[i] > grade[i-1])
				reward[i] = reward[i-1] + 1;
            else if(grade[i] > grade[i+1] && grade[i] > grade[i-1])
               reward[i] = reward[i-1] + 1;
            else if(grade[i] < grade[i+1] && grade[i] < grade[i-1])
                reward[i] = 1;
            else if(grade[i] > grade[i+1] && grade[i] < grade[i-1])
            {
                int tmp = i - 1;
                reward[i] = reward[i+1] + 1;
                while(tmp >= 0 && grade[tmp] > grade[tmp+1] && reward[tmp] <= reward[tmp+1])
                {
                    reward[tmp] = reward[tmp+1] + 1;
                    tmp --;
                }
            }
            
            cout << reward[i] << "--";
		}
		if(grade[N-1] > grade[N-2])
            reward[N-1] = reward[N-2] + 1;
		cout << reward[N-1] << endl;
		int ret = 0;
		for(int i=0; i<N; i++)
			ret += reward[i];
		//ret = accumulate(reward.begin(), reward.end(), 0);
		cout << ret << endl;
	}
	return 0;
}
