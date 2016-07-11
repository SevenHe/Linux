/*
 * 开发一个简单错误记录功能小模块，能够记录出错的代码所在的文件名称和行号。 
 处 理:                     *
 1.记录最多8条错误记录，对相同的错误记录(即文件名称和行号完全匹配)只记录一条，错误计数增加；(文件所在的目录不同，文件名和行号相同也要合并)
 2.超过16个字符的文件名称，只记录文件的最后有效16个字符；(如果文件名不同，而只是文件名的后16个字符和行号相同，也不要合并)
 3.输入的文件可能带路径，记录文件名称不能带路径
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

map<pair<string, int>, int> fileName_map;

int cmp(const pair<string, pair<int, int> >&x, const pair<string, pair<int, int> > &y)
{
	if(x.second.second == y.second.second)
	{
		//cout << x.first << x.second.first << " : " << fileName_map[make_pair(x.first, x.second.first)] << endl;
		//cout << y.first << y.second.first << " : " << fileName_map[make_pair(y.first, y.second.first)] << endl;
		return fileName_map[make_pair(x.first, x.second.first)] < fileName_map[make_pair(y.first, y.second.first)];
	}
	else
		return x.second.second> y.second.second;
}

int main()
{
	string s;
	int lineNr;
	int index = 0;
	map<string, map<int, int> > data_map;
	vector< pair<string, pair<int, int> > > sort_vector;
	while(cin >> s >> lineNr)
	{
		string sub;
		int subi;
		if((subi = s.find_last_of('\\')) != -1)
			sub = s.substr(subi+1);
		else
			sub = s;
		if(fileName_map.find(make_pair(sub, lineNr)) == fileName_map.end())
			fileName_map[make_pair(sub, lineNr)] = index++;
			//cout << sub << "," << lineNr << "," << fileName_map[make_pair(sub, lineNr)] << endl;
		data_map[sub][lineNr] ++;
	}
	for(map<string, map<int, int> >::iterator it = data_map.begin();
			it != data_map.end(); it++)
		for(map<int, int>::iterator it2 = it->second.begin();
				it2 != it->second.end(); it2++)
			sort_vector.push_back(make_pair(it->first, make_pair(it2->first, it2->second)));
	sort(sort_vector.begin(), sort_vector.end(), cmp);
	for(int i=0; i<8 && i<sort_vector.size(); i++)
	{
		int len;
		if((len = sort_vector[i].first.size()) > 16)
			sort_vector[i].first = sort_vector[i].first.substr(len-16);
		cout << sort_vector[i].first << " " << sort_vector[i].second.first 
			<< " " << sort_vector[i].second.second << endl;
	}
	return 0;
}
