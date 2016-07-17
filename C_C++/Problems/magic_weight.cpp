/*
   给出 n 个字符串，对于每个 n 个排列 p，按排列给出的顺序(p[0] , p[1] … p[n-1])依次连接这 n 个字符串都能得到一个长度为这些字符串长度之和的字符串。所以按照这个方法一共可以生成 n! 个字符串。
   一个字符串的权值等于把这个字符串循环左移 i 次后得到的字符串仍和原字符串全等的数量，i 的取值为 [1 , 字符串长度]。求这些字符串最后生成的 n! 个字符串中权值为 K 的有多少个。
   注：定义把一个串循环左移 1 次等价于把这个串的第一个字符移动到最后一个字符的后面。
   
   ==========
   在寻找相等或者位移后相等的子序列时，可以找到循环节，再用字符串长度除以循环节长度，则是可以出现的最多次数，减少循环时间！！
   若std::next_permutation超时，很可能是不让使用STL的全排列（浪费了很多时间），自己写一个全排列，然后计算尝试一下。
   自己写全排列的思路是，一个数组传递选择，一个公共数组（也可传递局部）保存哪个值已经使用！
   在当前位置，选择一个值，然后进行下一次全排列，再恢复状态，选择下一个作为当前位置的值，不断n循环+递归！！
   注意，下标和状态一一对应！！
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

vector<string> str;
vector<bool> flag;
int n,K;
int count1;

void permutation(int pos, vector<int> use)
{
    if(pos == n)
    {
        string s;
        for(int i=0; i<n; i++)
            s += str[use[i]];
        
        int tmp = 1;
        string tmps = s;
        for(int i=0; i<s.size()/2; i++)
        {
            tmps = tmps.substr(1) + tmps[0];
            if(tmps == s)
            {
                tmp = s.size() / (i+1);
                break;
            }
        }
        if(tmp == K)
            count1++;
        return;
    }
    for(int i=0; i<n; i++)
    {
        if(flag[i])
        {
            use.push_back(i);
            flag[i] = false;
            permutation(pos+1, use);
            flag[i] = true;
            use.erase(use.end()-1);
        }
    }
}
int main()
{
	cin >> n >> K;
    str.resize(n);
    flag.resize(n);
	int index = 0;
    int N = n;
	while(N--)
	{
		string s;
		cin >> s;
		str[index] = s;
		flag[index] = true;
		index ++;
	}
	vector<int> use;
    permutation(0, use);
	
	cout << count1 << endl;
	return 0;
}
/*
Poly created!
*/
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Poly
{
	public:
		vector<int> data;
		bool is_poly()
		{
			if(data.size() < 3)
				return false;
			sort(data.begin(), data.end());
			int sum = accumulate(data.begin(), data.end()-1, 0);
			if(sum <= data[data.size()-1])
				return false;
			return true;
		}
		void op(int i, int opt)
		{
			if(i == 1)
				data.push_back(opt);
			else if(i == 2)
			{
				vector<int>::iterator it = find(data.begin(), data.end(), opt);
				data.erase(it);
			}
			if(is_poly())
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
		}
};

int main()
{
	Poly p;
	int n;
	cin >> n;
	while(n--)
	{
		int i, o;
		cin >> i >> o;
		p.op(i, o);
	}
	return 0;
}
*/

