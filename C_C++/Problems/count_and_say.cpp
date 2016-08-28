#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string countAndSay(int n) {
	string ret = "1";
	stringstream ss;

	for (int i=1; i<n; i++) {
		string tmp = ret;
		ret = "";

		int cnt = 1;
		int len = tmp.size();
		char last =  tmp[0];
		for (int j=1; j<len; j++) {
			if (tmp[j] == last) {
				cnt++;
			}
			else {
				ss.str("");
				ss << cnt;
				ret += ss.str();
				ret += last;
				last = tmp[j];
				cnt = 1;
			}
		}

		ss.str("");
		ss << cnt;
		ret += ss.str();
		ret += last;
	}
	return ret;
}

int main()
{
	int n;
	while (cin >> n) {
		cout << countAndSay(n) << endl;
	}
	return 0;
}
