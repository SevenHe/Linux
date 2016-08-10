/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ftp_class.h
 * Author: Seven
 *
 * Created on August 8, 2016, 9:12 PM
 */

#ifndef FTP_CLASS_H
#define FTP_CLASS_H
#include <cstring>

#include <boost/thread/detail/move.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/concurrent_queues/sync_queue.hpp>
#include <boost/thread/csbl/vector.hpp>
using namespace boost;

#ifndef FTP_PARAM_H
#include "ftp_param.h"
#endif

/* 
 * User connection, FTP client.
 */
class FTPClient
{
	private:
		int id;
        int data_fd;
        int data_port;  /* FOR PASV MODE */
        char pswd[USER_INFO_LENGTH];
        char buffer[FILE_MAX_BUFFER];
        bool in_transmission;
        uint8_t mode;
        std::ofstream ofs;
        std::ifstream ifs;
	public:
        bool is_logged;
        char last_c_feedback[FB_MAX_LENGTH];
        char last_d_feedback[FB_MAX_LENGTH];
        char user[USER_INFO_LENGTH];
        char file_name[MAX_FILE_NAME];
        
        /* Constructor */
        FTPClient()
        {
            this->id = -1;
            this->data_fd = -1;
            this->data_port = 0;
            this->is_logged = false;
            this->in_transmission = false;
            this->mode = 0;     /* 0 FOR OUTPUT, 1 FOR INPUT */
        }
        
        /* Destructor */
        ~FTPClient() {}
        
        /* Functional functions */
        bool ftp_open(const std::string&, const bool, int);
        bool ftp_close();
        /* just for data connections */
        string ftp_write();     
        size_t ftp_recv();
        
        char* get_buffer()
        {
            return this->buffer;
        }
        
        void clear_file_buffer();
        
        /* ID GETTER AND SETTER */
		int get_id()
		{
			return this->id;
		}
        
		void set_id(const int id)
		{
			this->id = id;
		}
		
        /* DATA_FD GETTER AND SETTER */
        int get_data_fd();
        
        void set_data_fd(const int dfd)
        {
            this->data_fd = dfd;
        }
        
		/* DATA_PORT GETTER AND SETTER */
		int get_data_port()
        {
            return this->data_port;
        }
        
        void set_data_port(const int port)
        {
            this->data_port = port;
        }
        /* DATA TRANSFER MODE */
        uint8_t get_mode()
        {
            return this->mode;
        }
        
        void set_mode(const uint8_t m)
        {
            this->mode = m;
        }
        
        /* OTHER NECESSARY FUNCTIONS */
        void set_password(const char* password)
        {
            strncpy(this->pswd, password, USER_INFO_LENGTH);
        }
    
        
        void reset()
        {
            this->id = -1;
            this->data_fd = -1;
            this->data_port = 0;
            this->is_logged = false;
            this->in_transmission = false;
            this->mode = 0;
            memset(last_c_feedback, 0, sizeof(last_c_feedback));
            memset(last_d_feedback, 0, sizeof(last_d_feedback));
            memset(user, 0, sizeof(user));
            memset(pswd, 0, sizeof(pswd));
            memset(buffer, 0, sizeof(buffer));
            memset(file_name, 0, sizeof(file_name));
        }
};

/* The work struct in the thread. */
struct work
{
    /* 
     * These datum can be put into a base class, 
     * and do a template to pass them in the same interface.
     */
    FTPClient& c;
    work (FTPClient& client) : c(client) {}
    void run();
};

/* Thread pool, to manage the threads in concurrency. */
class thread_pool
{
private:
    typedef scoped_thread<> thread_t;
    typedef csbl::vector<thread_t> thread_vector;
    typedef condition_variable con_var;
    
    con_var cv;
    mutex mutex;
    concurrent::sync_queue<work> work_queue;
    thread_vector threads;
    
    void worker_thread()
    {
        for (;;) {
            mutex::scoped_lock lock(this->mutex);
            cv.wait(lock);
            if (work_queue.empty())
                continue;
            work& w = work_queue.pull();
            w.run();
        }
    }
public:
    thread_pool(unsigned int count) 
    {
        /* Adding a try catch is more powerful, but this place just for use. */
        for (unsigned int i=0; i<count; i++) {
            thread th(&thread_pool::worker_thread);
            threads.push_back(thread_t(boost::move(th)));
        }
    }
    
    ~thread_pool()
    {
        close();
    }
    
    /* Push a work, it will run automatically. */
    bool push_work(const work& w)
    {
        if (work_queue.try_push(w) == queue_op_status::success) {
            cv.notify_one();
            return true;
        }   
        return false;
    }
    
    /* Join all the threads. */
    void join_all()
    {
        for (unsigned int i=0; i<threads.size(); i++)
            threads[i].join();
    }
    
    /* Close the management queue, so just for destroying. */
    void close()
    {
        work_queue.close();
    }
};


#endif /* FTP_CLASS_H */

