#include <iostream>
#include <cinttypes>
using namespace std;

#include "ftp_param.h"

class FTPClient {
private:
	/* the index in the available queue! */
    int16_t id;

	/* mapping the data link with this client */
    uint16_t data_fd;
    uint16_t data_port; /* FOR PASV MODE */

	/* flags */
    uint16_t mode : 8;
	uint16_t status : 8;

	/* buffer - times of 8 */
    char pswd[USER_INFO_LENGTH];
    char buffer[FILE_MAX_BUFFER];

	/* XXX - file pointers */
	FILE* ofs;
	FILE* ifs;

    //std::ofstream ofs;
    //std::ifstream ifs;
public:
    bool is_logged;
	
	/* the last client link feedback, make it alignment - times of 8 + 7 */
    char last_c_feedback[FB_MAX_LENGTH];

	/* the cache of the file name - times of 8 + 1 for the next feedback */
    char file_name[MAX_FILE_NAME];

	/* the last data link feedback */
    char last_d_feedback[FB_MAX_LENGTH];
    /* 
     * When using strncpy with a const obj, there is a bug,
     * that is we need to convert user from const char* to char*.
     */
    char user[USER_INFO_LENGTH];
};

class TT {
	bool i;
	char a[5];
	char b[2];
	int c;
};

int main()
{
	cout << "sizeof(FTPClient):" << sizeof(FTPClient) << endl;
	cout << "sizeof(TT):" << sizeof(TT) << endl;

	return 0;
}
