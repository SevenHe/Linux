/*
 * 扑克牌游戏大家应该都比较熟悉了，一副牌由54张组成，含3~A，2各4张，小王1张，大王1张。牌面从小到大用如下字符和字符串表示（其中，小写joker表示小王，大写JOKER表示大王）:) 
 * 3 4 5 6 7 8 9 10 J Q K A 2 joker JOKER 
 * 输入两手牌，两手牌之间用“-”连接，每手牌的每张牌以空格分隔，“-”两边没有空格，如：4 4 4 4-joker JOKER
 * 请比较两手牌大小，输出较大的牌，如果不存在比较关系则输出ERROR
 * 
 * 基本规则：
 * （1）输入每手牌可能是个子，对子，顺子（连续5张），三个，炸弹（四个）和对王中的一种，不存在其他情况，由输入保证两手牌都是合法的，顺子已经从小到大排列；
 * （2）除了炸弹和对王可以和所有牌比较之外，其他类型的牌只能跟相同类型的存在比较关系（如，对子跟对子比较，三个跟三个比较），不考虑拆牌情况（如：将对子拆分成个子）
 * （3）大小规则跟大家平时了解的常见规则相同，个子，对子，三个比较牌面大小；顺子比较最小牌大小；炸弹大于前面所有的牌，炸弹之间比较牌面大小；对王是最大的牌；
 * （4）输入的两手牌不会出现相等的情况。
 * 
 * 答案提示：
 * （1）除了炸弹和对王之外，其他必须同类型比较。
 * （2）输入已经保证合法性，不用检查输入是否是合法的牌。
 * （3）输入的顺子已经经过从小到大排序，因此不用再排序了.
 */

/*
 * 某些觉得复杂的地方，写一个函数，取得返回值，则逻辑变得很清楚，不要强加在一起写。
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

#define SINGLE 1
#define PAIR 2
#define TRIPLE 3
#define BOMB 4
#define STRAIGHT 5
#define DJOKER 0

int split_card(string s)
{
	int count = 0;
	for(int i=0; i<s.size(); i++)
		if(s[i] == ' ')
			count ++;

	//cout << s << ":" << count+1 << endl;
	return count + 1;
}

int get_value(string s)
{
	if(s.size() == 1)
		return s[0]-'0';
	else if(s.size() == 2)
		if(s.find("10") < s.size())
			return 10;
	return -1;
}

int card_type(string s)
{
	int len = split_card(s);
	switch(len)
	{
		case 1: 
			return SINGLE;
		case 2:
			if(s.find("joker") > s.size())
				return PAIR;
			else
				return DJOKER;
		case 3:
			return TRIPLE;
		case 4:
			return BOMB;
		case 5:
			return STRAIGHT;
	}

}

int find_min(string s)
{
	vector<int> card;
	string tmp;
	for(int i=0; i<s.size(); i++)
	{
		if(s[i] != ' ')
			tmp += s[i];
		else
		{
			card.push_back(get_value(tmp));
			cout << tmp << ":" << get_value(tmp) << endl;
			tmp.clear();
		}
	}
	card.push_back(get_value(tmp));
	sort(card.begin(), card.end());
	return card[0];
}
	

int main()
{
	string s1;
	string s2;
	string s;
	bool need_switch = false;
	while(cin >> s)
	{
		// return npos
		if(s.find('-') < s.size())
		{
			int tpos = s.find('-');
			s1 += s.substr(0, tpos);
			need_switch = true;
		}
		if(!need_switch)
		{
			s1 += s;
			s1 += ' ';
		}
		else
		{
			int pos = s.find('-');
			if(pos > s.size())
				s2 += s;
			else
				s2 += s.substr(pos+1);
			s2 += ' ';
		}
	}
	s2.erase(s2.end()-1);
	//cout << s1 << "," << s2 << endl;
	int s1_type = card_type(s1);
	int s2_type = card_type(s2);
	if(s1_type == s2_type)	
	{
		int s1V = find_min(s1);
		int s2V = find_min(s2);
		if(s1V > s2V)
			cout << s1 << endl;
		else
			cout << s2 << endl;
	}
	else if(s1_type == BOMB && (s2_type == SINGLE || s2_type == PAIR || s2_type == TRIPLE
					|| s2_type == STRAIGHT))
		cout << s1 << endl;
	else if(s2_type == BOMB && (s1_type == SINGLE || s1_type == PAIR || s1_type == TRIPLE
					|| s1_type == STRAIGHT))
		cout << s2 << endl;
	else if(s1_type == DJOKER)
		cout << s1 << endl;
	else if(s2_type == DJOKER)
		cout << s2 << endl;
	else
		cout << "ERROR" << endl;
	return 0;
}
