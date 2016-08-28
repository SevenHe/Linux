/*
 * It is better to select IDE to develop programs.
 * But to debug the program, use the terminal! 
 */

/* 
 * File:   ftp_class.h
 * Author: Seven
 *
 * Created on August 8, 2016, 9:12 PM
 */

#ifndef FTP_CLASS_H
#define FTP_CLASS_H
#include <iostream>
#include <fstream>
#include <cstring>

#include <boost/thread/mutex.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/container/vector.hpp>

/* 
 * Due to the server, we need to CTRL+C to exit it. 
 * But the boost catches this as an error, so we relieves it. 
 */
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
#undef BOOST_THREAD_PROVIDES_INTERRUPTIONS
#endif

#ifndef FTP_PARAM_H
#include "ftp_param.h"
#endif

namespace mine {
    static bool ths_in_use = false;
}

/* 
 * User connection, FTP client.
 * Alignment of memory and compression in the future!
 */
class FTPClient {
private:
    int id;
    int data_fd;
    int data_port; /* FOR PASV MODE */
    char pswd[USER_INFO_LENGTH];
    char buffer[FILE_MAX_BUFFER];
    uint8_t mode;
    std::ofstream ofs;
    std::ifstream ifs;
public:
    bool is_logged;
    char last_c_feedback[FB_MAX_LENGTH];
    char last_d_feedback[FB_MAX_LENGTH];
    /* 
     * When using strncpy with a const obj, there is a bug,
     * that is we need to convert user from const char* to char*.
     */
    char user[USER_INFO_LENGTH];
    char file_name[MAX_FILE_NAME];

    /* Constructor */
    FTPClient() {
        this->id = -1;
        this->data_fd = -1;
        this->data_port = 0;
        this->is_logged = false;
        this->mode = 0; /* 0 FOR OUTPUT(ofstream), 1 FOR INPUT(ifstream) */
    }

    /* Copy Constructor for the ifstream and ofstream. */
    FTPClient(const FTPClient& fc) {
        /* 
         * We do not use this, but just make compiler happy,
         * because of compiler check the ifstream and ofstream has a copy constructor,
         * but they do not have, so we make a outside copy constructor to meet it.
         */
    }
    
    /* Assign Constructor to avoid boost's errors. */
    FTPClient& operator=(const FTPClient& fc)
    {
        /* nothing */
        return *this;
    }

    /* Destructor */
    ~FTPClient() {
    }

    /* Functional functions */
    bool ftp_open(const std::string&, const bool o = true);
    bool ftp_close();
    /* just for data connections */
    size_t ftp_write();
    std::string ftp_recv();

    char* get_buffer() {
        return this->buffer;
    }

    void clear_file_buffer() {
        memset(this->file_name, 0, sizeof (this->file_name));
        memset(this->buffer, 0, sizeof (this->buffer));
        memset(this->last_d_feedback, 0, sizeof (this->last_d_feedback));
    }

    /* ID GETTER AND SETTER */
    int get_id() {
        return this->id;
    }

    void set_id(const int id) {
        this->id = id;
    }

    /* DATA_FD GETTER AND SETTER */
    int get_data_fd() {
        return this->data_fd;
    }

    void set_data_fd(const int dfd) {
        this->data_fd = dfd;
    }

    /* DATA_PORT GETTER AND SETTER */
    int get_data_port() {
        return this->data_port;
    }

    void set_data_port(const int port) {
        this->data_port = port;
    }

    /* DATA TRANSFER MODE */
    uint8_t get_mode() {
        return this->mode;
    }

    void set_mode(const uint8_t m) {
        this->mode = m;
    }

    /* OTHER NECESSARY FUNCTIONS */
    void set_password(const char* password) {
        strncpy(this->pswd, password, USER_INFO_LENGTH);
    }

    void reset() {
        this->id = -1;
        this->data_fd = -1;
        this->data_port = 0;
        this->is_logged = false;
        this->mode = 0;
        memset(last_c_feedback, 0, sizeof (last_c_feedback));
        memset(last_d_feedback, 0, sizeof (last_d_feedback));
        memset(user, 0, sizeof (user));
        memset(pswd, 0, sizeof (pswd));
        memset(buffer, 0, sizeof (buffer));
        memset(file_name, 0, sizeof (file_name));
    }
};

/* The work struct in the thread */
struct work {
    /* 
     * These datum can be put into a base class, 
     * and do a template to pass them in the same interface.
     */
    FTPClient* c;
    
    work() {
        this->c = NULL;
    }

    work(FTPClient* client) : c(client) {
    }

    /* Copy constructor and Assign constructor because of a pointer.*/
    work(const work& w) {
        if (w && w.c)
            this->c = w.c;
    }

    work& operator=(const work& w) {
        if (this == &w)
            return *this;
        else if (w && w.c)
            this->c = w.c;
        return *this;
    }

    ~work() {
        /* nothing */
    }

    /* the job */
    void run();
};

/* 
 * Boost::thread as an struct to use another template. 
 * else, the thread would use a template that do not support the vector.
 */
template <typename T = boost::thread>
struct thread_T {
    T* t;

    thread_T() {
        t = NULL;
    }

    /* 
     * boost library needs that copy the struct into the queue, 
     * so there is a problem when using a pointer!
     */
    thread_T(const thread_T<T>& tT) {
        if (tT && tT.t)
            this->t = tT.t;
    }

    thread_T<T>& operator=(const thread_T<T>& tT) {
        if (this == &tT)
            return *this;
        else if (tT && tT.t)
            this->t = tT.t;
        return *this;
    }

    ~thread_T() {
        if (!mine::ths_in_use && this->t)
            delete t;
    }

};

/* Thread pool, to manage the threads in concurrency. */
class thread_pool {
private:
    /* use scoped_thread in the future. */
    typedef thread_T<> thread_t;
    typedef boost::container::vector<thread_t> thread_vector;
    typedef boost::condition_variable con_var;
    typedef boost::lockfree::capacity<FTP_MAX_QUEUE> capacity;
    typedef work* work_t;

    con_var cv;
    boost::mutex tp_mutex;
    /*
     * Objects may have other objects just like std::string,
     * which did not have a trivial constructor or destructor..
     * So a better way is to store the pointer! 
     */
    boost::lockfree::queue<work_t, capacity> work_queue;
    thread_vector threads;

    /* 
     * The worker_thread blocks in this loop. 
     * As a member function, it must be binded with this ptr.
     */
    void worker_thread() {

        for (;;) {
            boost::mutex::scoped_lock lock(this->tp_mutex);
            cv.wait(lock);
            if (work_queue.empty())
                continue;
            work_t w;
            if (work_queue.pop(w))
                w->run();
            else
                thread_run_error();
        }

    }

    /* Just for now. */
    void thread_run_error() {
        cout << FTP_LOG_HEAD << " Thread pool failed to pop a work!" << endl;
    }

public:

    thread_pool(unsigned int count) {
        mine::ths_in_use = true;
        /* Adding a try catch is more powerful, but this place just for use. */
        cout << " Initialize the thread pool :" << endl;
        for (unsigned int i = 0; i < count; i++) {
            /* use boost::move in the future to get more compatible. */
            /* And now, it is an ADL problem, conflicts.*/
            thread_t tt;
            tt.t = new boost::thread(boost::bind(&thread_pool::worker_thread, this));
            threads.push_back(tt);
            cout << "   Thread " << i << " in the thread pool"
                 << " is going to run!" << endl;
        }
    }

    ~thread_pool() {
        close();
    }

    /* Push a work, it will run automatically. */
    bool push_work(work_t w) {
        if (w->c && work_queue.push(w)) {
            cv.notify_one();
            return true;
        }
        return false;
    }

    /* Join all the threads. */
    void join_all() {
        for (unsigned int i = 0; i < threads.size(); i++) {
            threads[i].t->join();
        }
    }

    /* Close the management queue, so just for destroying. */
    void close() {
        mine::ths_in_use = false;
        
        /* nothing else to do now! */
    }
};



#endif /* FTP_CLASS_H */

