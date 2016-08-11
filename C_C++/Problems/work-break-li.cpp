/*
   Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.
   Return all such possible sentences.
   For example, given
   s ="catsanddog",
   dict =["cat", "cats", "and", "sand", "dog"].
   A solution is["cats and dog", "cat sand dog"].
 */
#include <iostream>
#include <tr1/unordered_set>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using namespace std::tr1;

vector<string> res;

void display(const string& s)
{
	cout << "=> " << s << endl;
}

void getNext(string s, unordered_set<string>& dict, string ret)
{
	int len = s.size();
	for (int i=0; i<len; i++) {
		string tmp = s.substr(0, i+1);
		if (dict.find(tmp) == dict.end())
			continue;
		if (i+1 == len) {
			ret += tmp;
			res.push_back(ret);
			return;
		}
		else
			getNext(s.substr(i+1), dict, ret+tmp+" ");
	}
}

vector<string> wordBreak(string s, unordered_set<string> &dict) {
	if (s.empty())
		return res;
	int len = s.size();
	for (int i=0; i<len; i++) {
		string ret;
		string tmp = s.substr(0, i+1);
		if (dict.find(tmp) == dict.end())
			continue;
		ret += tmp;
		ret += " ";
		if (i+1 == len) {
			ret.erase(ret.end()-1);
			res.push_back(ret);
		}
		else
			getNext(s.substr(i+1), dict, ret);
	}
	return res;
}


int main() {
	unordered_set<string> dict;
	dict.insert("aaa");
	dict.insert("aaaa");
	string s = "aaaaaaa";
	wordBreak(s, dict);
	for_each(res.begin(), res.end(), display);
	return 0;
}

