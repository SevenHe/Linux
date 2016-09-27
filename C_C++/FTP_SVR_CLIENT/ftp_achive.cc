/*
 * Achieve the complex functions in the classes.
 */
#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <exception>
#include <cerrno>
using namespace std;

#include "ftp_class.hpp"

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

        /* ifs.read() when reaching the end, may set the failbit, 
         * So we just judge if it got the end.
         */
        if (!this->ifs.eof())
            return false;
    }
    return true;
}

/* For copying files from the client. 
 * Get the data until a FTP_FTR_CMD_ENDALL.
 */
string FTPClient::ftp_recv()
{
    string ret;
    char* buffer = this->get_buffer();
    int recvNum = read(this->get_data_fd(), buffer, FILE_MAX_BUFFER);
    if (recvNum <= FILE_MAX_BUFFER && recvNum > 0) {
        this->ofs.write(buffer + 1, recvNum - 1);
        
        if (!ofs.bad())
            cout << FTP_LOG_HEAD << " Write into " << this->file_name
                << ", size " << recvNum - 1 << endl;
        else
            cout << FTP_LOG_HEAD << " Fail to write datum into a file." << endl;
        
        if (buffer[0] == FTP_FTR_CMD_CONTINUE) {
            ret = FTP_FTR_CMD_CONTINUE;
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

/* For putting file into the client. 
 * Put the data until the file gets the end and then send an ENDALL.
 */
size_t FTPClient::ftp_write()
{
    int ret = 0;
    char* buffer = this->get_buffer();
    this->ifs.read(buffer + 1, FILE_MAX_BUFFER - 1);

    /* Real bytes have read. */
    ret = ifs.gcount();

    if (!ifs.eof() && ret >= FILE_MAX_BUFFER - 1)
        buffer[0] = FTP_FTS_CMD_CONTINUE;
    else if (ifs.eof() || ret == 0)
        buffer[0] = FTP_FTS_CMD_ENDALL;


    if (ret != 0) {
        cout << FTP_LOG_HEAD << " Read from " << this->file_name << ", size "
                << ret;
        if (ifs.eof() && buffer[0] == FTP_FTS_CMD_ENDALL)
            cout << " and reach the end" << endl;
        else
            cout << " to send to the client" << endl;
    }

    return ret;
}

void work::run()
{
    /*
     * TODO -- 
     * As a sending end, we have the priority to send the data whenever we are free.
     * But when we receive the data from the client, we don't know how the network is,
     * So we could to wait the client to send the data to avoid clearing the buffer.
     * That is, we should block it.
     */
    while (1) {
        if (this->c->get_mode()) {
            int ret = this->c->ftp_write();
            /* In the future, judge the client state to ensure the connection! */
            if (ret != 0) {
                ret = write(this->c->get_data_fd(), this->c->get_buffer(), ret);
            }
            if (ret >= 0 && (this->c->get_buffer()[0]) == FTP_FTS_CMD_ENDALL) {
                int recv_num = read(this->c->get_data_fd(), this->c->last_d_feedback, FB_MAX_LENGTH);
                if (recv_num >= 0 && this->c->last_d_feedback[0] == FTP_FTS_CMD_ENDALL) {
                    close(this->c->get_data_fd());
                    cout << FTP_LOG_HEAD << " Data connection " << this->c->get_data_fd()
                            << " shut down normally." << endl;
                    if (this->c->ftp_close())
                        cout << FTP_LOG_HEAD << " Complete transferring ==> "
                            << this->c->file_name << endl;
                    else
                        cout << FTP_LOG_HEAD << " Fail to close the file. " << endl;
                    this->c->clear_file_buffer();
                    break;
                }
                else {
                    /* Just wait the client msg or get an error! */
                }
            }
            else if ((this->c->get_buffer()[0]) == FTP_FTS_CMD_CONTINUE) {
                /* Just in file transferring
                 * Do statistics in the future.
                 */
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


