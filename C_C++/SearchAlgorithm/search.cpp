#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;

#include <dirent.h>

/* In the future, this can be input as a argument */
#define DIR_PATH "/home/seven/Downloads/linux-4.5.5/"

extern int index_detect_output(const char*);
extern string index_file_name;
int sub_dir_iteration(const char*, ofstream&);


int main()
{
	DIR* dp;
	struct dirent* file;
	clock_t start,finish;
	int count;
	
	/* the global file handle */
	ofstream ofs(index_file_name.c_str(), ios::app);
	
	start = clock();
	dp = opendir(DIR_PATH);
	if(!dp)
	{
		cerr << "Open directory error!" << endl;
		return 1;
	}

	/* This can be debugged, so do not put it into a function */
	while((file = readdir(dp)) != NULL)
	{
		string tmp_path(DIR_PATH);
		tmp_path.append(file->d_name);
		/* A dir must end with '/' */
		if(file->d_type == DT_DIR)
		{
			if(file->d_name[0] == '.')
				continue;
			tmp_path += '/';
			count = sub_dir_iteration(tmp_path.c_str(), ofs);
		}
		/* for debugging, but the main kernel dir has no .c file. */
		/*
		else if(file->d_type == DT_REG)
		{
			int slen = strlen(file->d_name);
			if(file->d_name[slen-1] == 'c' && file->d_name[slen-2] == '.')
				ret = index_detect_output(tmp_path.c_str());
		}
		if(ret <= 0);	// nothing
		else
			ofs << ret << ":" << tmp_path << endl;
		*/
	}
	closedir(dp);
	ofs.close();
	finish = clock();
	cout << "Add index files: " << count << ", time: " << double((finish-start))*1000/CLOCKS_PER_SEC << "ms" << endl;
	return 0;
}

int sub_dir_iteration(const char* path, ofstream& ofs)
{
	DIR* sdp;
	struct dirent* sfile;
	int ret = 0;
	bool is_src = false;
	sdp = opendir(path);
	while((sfile=readdir(sdp)) != NULL)
	{
		string tmp_path(path);
		tmp_path.append(sfile->d_name);
		if(sfile->d_type == DT_DIR)
		{
			if(sfile->d_name[0] == '.')
				continue;
			/* must end with a '/' to avoid from no finding */
			tmp_path += '/';
			sub_dir_iteration(tmp_path.c_str(), ofs);
		}
		else if(sfile->d_type == DT_REG)
		{
			int slen = strlen(sfile->d_name);
			if(sfile->d_name[slen-1] == 'c' && sfile->d_name[slen-2] == '.')
			{
				is_src = true;
				ret = index_detect_output(tmp_path.c_str());
			}
		}
		if(ret <= 0)
			/* nothing */;
		else if(is_src)
			ofs << ret << ":" << tmp_path << endl;
		is_src = false;
	}
	closedir(sdp);
	return ret;
}


