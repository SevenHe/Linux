/*
请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配
*/
/*
解题思路,当按顺序过程的判断方法不简单时,要想到递归和迭代的方法,
该题则是判断前后的状态,每次判断一个状态后,后续的状态作为参数传递给下一次递归,
由于每个状态的后一个状态有N种,因此只要有一次递归成功,最后就可以返回一个True,特殊的情况并不多,
可以放在最前面考虑!
*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

bool rMatch(const char*, const char*);

bool match(const char* str, const char* pattern)
{
	if (str == NULL && pattern == NULL)
		return false;
	return rMatch(str, pattern);
}

bool rMatch(const char* s, const char* p)
{
	// real match!!
	if (*s == '\0' && *p == '\0')
		return true;
	// for "", ".*"
	if (*p == '.' && *(p+1) == '*' && *(p+2) == '\0')
		return true;
	cout << "Get: " << s << "," << p << endl;
	if (*s != '\0' && *p == '\0')
		return false;
	// 匹配一个字符,且后面不为*
	if ((*s == *p || *p == '.')&& *(p+1) != '*' && *s != '\0')
		return rMatch(s+1, p+1);
	// 匹配当前字符后,若后面是*,则有三种递归情况,而且此时s一定不能为\0,因为有s+1的传递
	else if ((*s == *p || *p == '.') && *(p+1) == '*' && *s != '\0')
		return rMatch(s, p+2) || rMatch(s+1, p) || rMatch(s+1, p+2);
	// 匹配不成功,但可以忽略字符*
	else if (*s != *p && *(p+1) == '*')
		return rMatch(s, p+2);
	// 完全不相等,类似于,a和b匹配!
	return false;
}

int main()
{
	string s;
	string pat;
	cin >> s >> pat;
	cout << match("", ".*") << endl;
	cout << match(s.c_str(), pat.c_str()) << endl;
	return 0;
}
