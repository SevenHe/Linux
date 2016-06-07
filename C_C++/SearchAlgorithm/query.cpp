#include <iostream>
#include <fstream>
#include <tr1/unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#include <signal.h>

#define MAX_SHOW_LINE 20

extern string index_file_name;
extern string output_file_name;
extern unsigned int m_c;
extern void run_as_a_master();
extern void run_as_a_slave();

/* for the identifier master/slave */
static short id = 0;

/* for the query */
tr1::unordered_map<string, vector<string> > index;
tr1::unordered_map<int, string> mapping;

void exit_normally(int signal)
{
	cout << "Exit!" << endl;
	exit(0);
}

vector<string> query(string key)
{
	// Completely todo-- approximately match them!
	//cout << "get input" << input << endl;
	tr1::unordered_map<string, vector<string> >::const_iterator mit = index.find(key);
	vector<string>::const_iterator vit;
	vector<string> result;
	bool has_found = false;
	unsigned int delimit = 0;
	if(mit != index.end())
	{
		vit = (mit->second).begin();
		has_found = true;
	}
	for(; has_found && vit != (mit->second).end(); vit++)
	{
		string tmp;
		string vl;
		//cout << "Get info: " << *it << endl;
		delimit = (*vit).find(',');			// xx,xx : file_no,line_no
		vl = (*vit).substr(0, delimit);
		//cout << "Get info: " << mapping[atoi(line.c_str())] << ", line " << (*vit).substr(delimit+1) << endl;
		tmp = "Info: ";
		tmp.append(mapping[atoi(vl.c_str())]);
		tmp.append(", line ");
		tmp.append((*vit).substr(delimit+1));
		result.push_back(tmp);
	}
	if(has_found)
		result.push_back("All is above.");
	else
		result.push_back("No result has been found.");

	return result;
}

int main()
{
	signal(SIGINT, &exit_normally);
	ifstream ifs_i(index_file_name.c_str());
	ifstream ifs_o(output_file_name.c_str());
	string input;
	string line;
	string key;
	string value;
	unsigned int delimit;
	short count;
	clock_t start, finish;
	start = clock();
	while(getline(ifs_i, line))
	{
		delimit = line.find(':');
		key = line.substr(0, delimit);
		value = line.substr(delimit+1);
		mapping[atoi(key.c_str())] = value;
	}
	while(getline(ifs_o, line))
	{	
		// approximately matching!!
		string app_key;
		unsigned int tmp;
		unsigned int cur;
		bool add_app_key = false;
		delimit = line.find(':');	
		key = line.substr(0, delimit);
		tmp = key.rfind(' ');
		if(tmp < m_c && key[tmp+1] != ' ')
		{
			// do not include the ' '
			app_key = key.substr(tmp+1);
			//cout << "get app_key: " << app_key << " from " << tmp << endl;
			add_app_key = true;
		}
		delimit += 1;
		while((cur = line.find(' ', delimit)) < m_c)
		{
			value = line.substr(delimit, cur - delimit);
			index[key].push_back(value);
			if(add_app_key)
				index[app_key].push_back(value);
			delimit = cur + 1;
			if(count < MAX_SHOW_LINE)
			{
				cout << "get key: " << key << ", value:" << value << endl;
				count ++;
			}
			else if(count == MAX_SHOW_LINE)
			{
				cout << "......" << endl;
				count ++;
			}
		}
	}
	finish = clock();
	cout << endl << "Read the database.....OK!" << endl;
	cout << "Elapsed time: " << double(finish-start)*1000/CLOCKS_PER_SEC << "ms" << endl << endl;
	
	ifs_i.close();
	ifs_o.close();

	/* cluster starts */
	if(0 == id)
	{
		cout << "Run as the master..." << endl;
		run_as_a_master();
	}
	else
	{
		cout << "Run as a slave..." << endl;
		run_as_a_slave();
	}
	return 0;
}


