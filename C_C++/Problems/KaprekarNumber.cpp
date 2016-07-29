#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
using namespace std;

int cmp(const char& x, const char& y)
{
	return x > y;
}

int main ()
{
	string s;
	while (cin >> s) {
		while (atoi(s.c_str()) != 6174) {
			string ns(s);
			sort(s.begin(), s.end(), cmp);
			sort(ns.begin(), ns.end());
			printf("%04d - %04d = ", atoi(s.c_str()), atoi(ns.c_str()));
			//cout << s << " - " << ns << " = ";
			int ret = atoi(s.c_str()) - atoi(ns.c_str());
			printf("%04d\n", ret);
			if (ret == 0)
				break;
			stringstream ss;
			ss << ret;
			s = ss.str();
		}
	}
	return 0;
}
