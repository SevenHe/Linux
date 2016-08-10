/*
 * Achieve the complex functions in the classes.
 */
#include <iostream>
#include <string>
#include <exception>
#include <unistd.h>
#include <fstream>
using namespace std;

#include "ftp_class.h"

/* Open a file in the server or get from the client. */
bool FTPClient::ftp_open(const string& path, const bool output = true, int flags = 0)
{
    if (output) {
        if (0 == flags)
            flags = ios::out;

        this->ofs.open(path.c_str(), flags);
        if (this->ofs.fail())
            return false;

        /* if success */
        this->set_mode(0);
    }
    else {
        if (0 == flags)
            flags = ios::in;

        this->ifs.open(path.c_str(), flags);
        if (this->ifs.fail())
            return false;

        this->set_mode(1);
    }
    return true;
}

/* Close the file. */
bool FTPClient::ftp_close()
{
    if (!this->get_mode()) {
        this->ofs.close();
        if (this->ofs.fail())
            return false;
    }
    else {
        this->ifs.close();
        if (this->ifs.fail())
            return false;
    }
    return true;
}

/* For copying file from the client. */
string FTPClient::ftp_recv()
{
    string ret;
    char* buffer = this->get_buffer();
    int recv = read(this->get_data_fd(), buffer, FILE_MAX_BUFFER);
    if (recv <= FILE_MAX_BUFFER && recv > 0) {
        if (buffer[0] == FTP_FTR_CMD_CONTINUE) {
            ret = FTP_FTR_CMD_CONTINUE; 
            this->ofs.write(buffer+1, recv);
            if (!ofs.bad())
                cout << FTP_LOG_HEAD << " Write into " << this->file_name
                     << ", size " << recv-1 << endl;
        }
        else if (buffer[0] == FTP_FTR_CMD_ENDALL) {
            ret = FTP_FTR_CMD_ENDALL;
            if (this->ftp_close())
                cout << FTP_LOG_HEAD << " Complete transferring ==> "
                     << this->file_name << endl;
            this->clear_file_buffer();
        }
    }
    else {
        close(this->get_data_fd());
        cout << FTP_LOG_HEAD << " Data connection " << this->get_data_fd()
             << " shut down." << endl;
        this->clear_file_buffer();
        ret = FTP_RSP_FT_END;
    }
        
    return ret;
}

/* For putting file into the client. */
size_t FTPClient::ftp_write()
{
    int ret = 0;
    char* buffer = this->get_buffer();
    this->ifs.read(buffer+1, FILE_MAX_BUFFER-1);
    if (!ifs.eof()) 
        buffer[0] = FTP_FTS_CMD_CONTINUE;
    else
        buffer[0] = FTP_FTS_CMD_ENDALL;
    
    ret = ifs.gcount();
    
    cout << FTP_LOG_HEAD << " Read from " << this->file_name << ", size "
         << ret << " to send to the client" << endl;
    
    return ret;  
}

void work::run()
{
    if (!this->c)
        return "";
    while (1) {
        int recv = 0;
        if (this->c.get_mode()) {
            recv = read(this->c.get_data_fd(), this->c.last_d_feedback, FB_MAX_LENGTH);
            if (recv > 0) {
                if (this->c.last_d_feedback[0] == FTP_FTS_CMD_CONTINUE) {
                    int ret = this->c.ftp_write();
                    if (ret > 0)
                        write(this->c.get_data_fd(), 
                                this->c.get_buffer(), FILE_MAX_BUFFER);
                }
                else if (this->c.last_d_feedback[0] == FTP_FTS_CMD_ENDALL) {
                    if (this->c.ftp_close()) 
                        cout << FTP_LOG_HEAD << " Complete transferring <== "
                             << this->c.file_name << endl;
                    this->c.clear_file_buffer();
                }
            }
            else {
                close(this->c.get_data_fd());
                cout << FTP_LOG_HEAD << " Data connection " << this->c.get_data_fd()
                     << " shut down." << endl;
                this->c.clear_file_buffer();
                break;
            }
        }
        else {
            string ret = this->c.ftp_recv();
            if (ret == FTP_RSP_FT_END)
                break;
            else {
                write(this->c.get_data_fd(), ret.c_str(), ret.size());
            }
        }
    }
}


