/*
int get_del_min(string s, int index)
{
	int len = s.size();
	int spos = s.find_last_of(s[index]);
	bool right_matched = false;
	if(spos == index)
		return len; 
	else
	{
		cout << "s1:" << s << ", index:" << index << endl;
		int back_len = 1;
		s = s.substr(index+1, spos-index-1);
		while(s.size() > 1)	
		{
			spos = s.find_last_of(s[0]);
			if(0 == spos)
			{
				s = s.substr(1);
				continue;
			}
			else
			{
				back_len ++;
				if(spos > 0)
					s = s.substr(1, spos-1);
				else
					break;
				if(spos == 1)
					right_matched = true;
			}
		}
		if(!right_matched)
			return len - 2*back_len - 1;
		else
			return len - 2*back_len;
	}
}


int main()
{
	string s;
	while(cin >> s)
	{
		int len = s.size();
		int del_min = len;
		for(int i=0; i<len; i++)
		{
			int tmp = get_del_min(s, i);
			cout << "get del_min: " << tmp << endl;
			if(tmp < del_min)
				del_min = tmp;
		}
		cout << del_min << endl;
	}

	return 0;
}
*/
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxsize=1010;
int temp[maxsize][maxsize];

int get_delete_number(string &s1){
	string s2(s1);
	reverse(s2.begin(),s2.end());//字符串反转
	//反转函数之后求最长公共子序列
	int len= s1.size();
	memset(temp,0,sizeof(temp));//对定义的字符串进行初始化
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++){//求最长公共子序列的方法
			if(s1[i]==s2[j])
				temp[i+1][j+1]=temp[i][j]+1;
			else
				temp[i+1][j+1]=max(temp[i][j+1],temp[i+1][j]);
			cout << "temp[" << i+1 << "][" << j+1 << "]:" << temp[i+1][j+1] << endl;
		}
	return len-temp[len][len];
}
int main(){
	string s;
	while(getline(cin,s)){
		cout<<get_delete_number(s)<<endl;
	}
}


