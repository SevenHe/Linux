#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

#include <dirent.h>

/* In the future, this can be input as a argument, */
#define DIR_PATH "/home/seven/Downloads/linux-4.5.5/fs/"

extern int index_detect_output(const char*);
extern string index_file_name;

int main()
{
	DIR* dp;
	struct dirent* file;
	int ret = 0;
	dp = opendir(DIR_PATH);
	if(!dp)
	{
		cerr << "Open directory error!" << endl;
		return 1;
	}

	ofstream ofs(index_file_name.c_str(), ios::app);
	while((file = readdir(dp)) != NULL)
	{
		string tmp_path(DIR_PATH);
		tmp_path.append(file->d_name);
		if(file->d_type == DT_DIR)
			continue;
		else if(file->d_type == DT_REG)
			ret = index_detect_output(tmp_path.c_str());
		if(ret <= 0)
			/* nothing */;
		else
			ofs << ret << ":" << tmp_path << endl;
	}
	closedir(dp);
	ofs.close();
	return 0;
}
