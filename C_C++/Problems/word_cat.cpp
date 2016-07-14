/*
 * 拉姆刚开始学习英文单词，对单词排序很感兴趣。
 * 如果给拉姆一组单词，他能够迅速确定是否可以将这些单词排列在一个列表中，使得该列表中任何单词的首字母与前一单词的为字母相同。
 * 你能编写一个程序来帮助拉姆进行判断吗？
 */
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    int N;
    while(cin >> N)
    {
        map<char, int> first;
        map<char, int> last;
        string s;
        while(N--)
        {
            cin >> s;
            int len = s.size();
            first[s[0]] ++;
            last[s[len-1]] ++;
        }
        map<char, int>::iterator fit = first.begin();
        map<char, int>::iterator lit = last.begin();
        int count = 0;
        while(fit != first.end())
        {
            if(fit->first != lit->first)
            {
                fit++;
                count++;
            }
            else if(fit->first == lit->first)
            {
                if(fit->second == lit->second)
                {
                    fit++;
                    lit++;
                }
                else
                {
                    count++;
                    if(count == 2)
                        break;
                    else
                        fit++;
                }
            }
        }
        if(lit != last.end())
            count ++;
        if(count > 2)
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
    }
    
    return 0;
}
