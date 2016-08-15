/*
 * Achieve the complex functions in the classes.
 */
#include <string>
#include <exception>
#include <cerrno>
#include <unistd.h>
using namespace std;

#include "ftp_class.h"

/* 
 * Open a file in the server or get from the client. 
 * Default arguments are just given by the definition in the class.h!
 */
bool FTPClient::ftp_open(const string& path, const bool output)
{
    if (output) {

        this->ofs.open(path.c_str());
        if (this->ofs.fail())
            return false;

        /* if success */
        this->set_mode(0);
    }
    else {

        this->ifs.open(path.c_str());
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

/* For copying files from the client. */
string FTPClient::ftp_recv()
{
    string ret;
    char* buffer = this->get_buffer();
    int recvNum = read(this->get_data_fd(), buffer, FILE_MAX_BUFFER);
    if (recvNum <= FILE_MAX_BUFFER && recvNum > 0) {
        if (buffer[0] == FTP_FTR_CMD_CONTINUE) {
            ret = FTP_FTR_CMD_CONTINUE;
            this->ofs.write(buffer + 1, recvNum-1);
            if (!ofs.bad())
                cout << FTP_LOG_HEAD << " Write into " << this->file_name
                    << ", size " << recvNum - 1 << endl;
        }
        else if (buffer[0] == FTP_FTR_CMD_ENDALL) {
            ret = FTP_FTR_CMD_ENDALL;
            if (this->ftp_close())
                cout << FTP_LOG_HEAD << " Complete transferring <== "
                    << this->file_name << endl;
            this->clear_file_buffer();
        }
    }
    else if (recvNum == 0) {
        /* -- Future features --*/
        /* May the network is busy, so just wait some loops because of aio conversation */
        ret = FTP_FTR_CMD_ENDALL;
    }
    else if (errno == EAGAIN || errno == EWOULDBLOCK) {
        /* The problem is that the sock file descriptor is asynchronized,
         * So in the kernel, there is no available connection in the queue.
         * We solve this by ignoring these two errors, just do next loop!
         */
        ret = FTP_FTR_CMD_CONTINUE;
    } 
    else {
        close(this->get_data_fd());
        cout << FTP_LOG_HEAD << " Data connection " << this->get_data_fd()
                << " happened to exit" << endl;
        cout << FTP_LOG_HEAD << " Info: " << strerror(errno) << endl;
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
    this->ifs.read(buffer+1, FILE_MAX_BUFFER - 1);
    
    /* Real bytes have read. */
    ret = ifs.gcount();
    
    if (!ifs.eof() && ret >= FILE_MAX_BUFFER-1)
        buffer[0] = FTP_FTS_CMD_CONTINUE;
    else
        buffer[0] = FTP_FTS_CMD_ENDALL;

    cout << FTP_LOG_HEAD << " Read from " << this->file_name << ", size "
            << ret << " to send to the client" << endl;

    return ret;
}

void work::run()
{
    while (1) {
        if (this->c->get_mode()) {
            int ret = this->c->ftp_write();
            if (ret == FILE_MAX_BUFFER - 1)
                write(this->c->get_data_fd(), this->c->get_buffer(), FILE_MAX_BUFFER);
            else if (ret >= 0 && *(this->c->get_buffer()) == FTP_FTS_CMD_ENDALL) {
                int recv_num = read(this->c->get_data_fd(), this->c->last_d_feedback, FB_MAX_LENGTH);
                if (recv_num >= 0 && this->c->last_d_feedback[0] == FTP_FTS_CMD_ENDALL) {
                    close(this->c->get_data_fd());
                    cout << FTP_LOG_HEAD << " Data connection " << this->c->get_data_fd()
                            << " shut down normally." << endl;
                    if (this->c->ftp_close())
                        cout << FTP_LOG_HEAD << " Complete transferring ==> "
                            << this->c->file_name << endl;
                    this->c->clear_file_buffer();
                    break;
                }
            }
            else {
                cout << FTP_LOG_HEAD << " An error in the cmd 'Get'!" << endl;
                break;
            }
        }
        else {
            string ret = this->c->ftp_recv();
            if (ret[0] == FTP_RSP_FT_END)
                break;
            else if (ret[0] == FTP_FTR_CMD_ENDALL) {
                write(this->c->get_data_fd(), ret.c_str(), ret.size());
                close(this->c->get_data_fd());
                cout << FTP_LOG_HEAD << " Data connection " << this->c->get_data_fd()
                        << " shut down normally." << endl;
                break;
            }
        }
    }
}


