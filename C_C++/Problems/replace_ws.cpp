/*
请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Solution {
	public:
	/* char* 传来的是复制的地址，而且必须是由[]声明的数组，char*是不可以更改的，因此用str重新填充，string
	* 或者在连续的地址上，重新赋值即可！
	*/
		void replaceSpace(char *str,int length) {
			int spaceNum=0;

			for(int i=0;i<length;i++)
			{
				if(str[i]==' ')
					spaceNum++;

			}    

			int newIndex=length+2*spaceNum;
			char *index=str+length;
			while(index>=str)
			{
				if(*index==' ')
				{
					str[newIndex--]='0';
					str[newIndex--]='2';
					str[newIndex--]='%';
				}
				else{
					str[newIndex--]=*index;
				}
				index--;
			}
		}
};

int main()
{
	int length = 100;
	char s[length];
	string str;
	/*
	int len = strlen(str.c_str());
	for(int i=0; i<len; i++)
		if(str[i] == ' ')
		{
			str = str.replace(i, 1, "");
			str = str.insert(i, "%20");
		}
	cout << str << endl;
	*/
	char test[101] = "hello world  iam ok";
	string tmp(test);
	Solution S;
	cout << test << endl;
	S.replaceSpace(test, 100);
	cout << test << endl;
	return 0;
}
