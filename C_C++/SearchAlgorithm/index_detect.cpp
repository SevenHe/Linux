#include <iostream>
#include <fstream>
#include <sstream> 		/* stringstream */
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/* May be 500 is enough for one line characters. */
#define INDEX_FILE "indexes/idx_path"
#define OUTPUT_FILE "indexes/LK_Index"
#define MAX_COLUMNS 500

string index_file_name = INDEX_FILE;
string output_file_name = OUTPUT_FILE;
unsigned int m_c = MAX_COLUMNS;

/* TODO--to judge it is a reference or definition, so need a embedded hash_map one-to-many */

int index_detect_output(const char* path)
{
	static int file_no = 0;
	ifstream in(path);
	/* no existence, no reading from it. */
	/*
	fstream ip(INDEX_FILE, ios::in);
	if(!ip)
	{
		ip.close();
		ip.open(INDEX_FILE, ios::out|ios::app);
		ip << file_no << ":" << path << endl;
		ip.close();
	}
	*/
	int line_nr = 1;
	string s;
	unordered_map<string, vector<string> > index;

	/* ostringstream uses the same cache with the ostream, so it will be not what you want
	 * And use this, << and >>, get it flush!
	 */
	stringstream ss;	/* for input and output */
	unsigned int tmpos;
	cout << "Enter --> " << path << endl;
	bool in_brackets = false;
	bool in_comments = false;
	bool in_macros = false;
	bool in_func_head = false;
	file_no++;
	while(getline(in, s))
	{

		/* find the macros with functions */
		tmpos = s.find('#');
		if(tmpos < MAX_COLUMNS && !in_macros)
		{
			tmpos = s.find('\\');
			if(tmpos < MAX_COLUMNS)
				in_macros = true;
		}
		else
		{
			if(in_macros)
			{
				tmpos = s.find('\\');
				if(tmpos > MAX_COLUMNS)
					in_macros = false;
				line_nr ++;
				continue;
			}
		}

		/* find the comments */
		tmpos = s.find('/');
		if(tmpos < MAX_COLUMNS && !in_comments)
		{
			
			if(s[tmpos+1] == '*')
			{
				in_comments = true;
				tmpos = s.find('*', tmpos+2);
				if(tmpos < MAX_COLUMNS && s[tmpos+1] == '/')
					in_comments = false;
				else
					/* just one line comment */;
				line_nr ++;
				continue;
			}
		}
		else
		{
			if(in_comments)
			{
				tmpos = s.find('*');
				if(tmpos < MAX_COLUMNS && s[tmpos+1] == '/')
					in_comments = false;
				line_nr ++;
				continue;
			}
		}

		/* TODO-- judge the function block to avoid from the special definition like this:
		 * func(...,
		 		int ()(),..
				...)
		 */
		/* find the functions' indexes */
		if(!in_brackets)
		{
			tmpos = s.find('{');
			if(0 == tmpos)
				in_brackets = true;
			else if(tmpos > MAX_COLUMNS)
			{
				tmpos = s.find('(');	
				if(tmpos < MAX_COLUMNS)
				{
					string key = s.substr(0, tmpos);
					string value;
					ss.clear();
					ss << file_no << "," << line_nr << endl;
					ss >> value;
					tmpos = s.rfind(')');
					if(tmpos == s.size()-1)
					{
						if(!in_func_head)
							index[key].push_back(value);
						else
							in_func_head = false;
					}
					else if(tmpos > MAX_COLUMNS)
					{
						if(!in_func_head)
						{		
							index[key].push_back(value);
							in_func_head = true;
						}
					}
					//cout << "key:" << key << ", value:" << value << endl;
					//cout << "file:" << file_no << ", line:" << line_nr << ", index:" << key << endl;
				}
			}
			else if(tmpos < MAX_COLUMNS) 	/* for macros block */
			{
				/*
				 * There is a better way, to do these similar things as different methods or modules!
				 */
				tmpos = s.find('#');
				if(tmpos == 0)
				{
					tmpos = s.find('(');
					if(tmpos < MAX_COLUMNS)
					{
						if(s[tmpos-1] != ' ')
						{
							string key = s.substr(0, tmpos);
							string value;
							ss.clear();
							ss << file_no << "," << line_nr;
							ss >> value;
							index[key].push_back(value);
						}
					//cout << "file:" << file_no << ", line:" << line_nr << ", index:" << key << endl;
					}
				}
			}
		}
		else
		{
			tmpos = s.find('}');
			if(tmpos == 0)
				in_brackets = false;
		}
		line_nr ++;
	}
	in.close();
	ofstream out(OUTPUT_FILE, ios::app);
	unordered_map<string, vector<string> >::const_iterator it = index.begin();
	vector<string>::const_iterator vit;
	while(it != index.end())
	{
		out << it->first << ":";
		cout << it->first << ":";
		for(vit = it->second.begin(); vit != it->second.end(); vit ++)
		{
			out << *vit << " ";
			cout << *vit << " ";
		}
		out << endl;
		cout << endl;
		//cout.flush();
		it ++;
	}
	out.close();
	return file_no;
}
