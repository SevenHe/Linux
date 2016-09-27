/*
 * XXX - there are some methods that have not been completed!
 */

/* 
 * File:   ftp_func.h
 * Author: Seven
 *
 * Created on August 8, 2016, 9:14 PM
 */

#ifndef FTP_FUNC_H
#define FTP_FUNC_H

void set_no_blocking(const int&);
static uint8_t judge_sock_type(std::tr1::unordered_map<int, int>&, const int&);
static void demap_socks(std::tr1::unordered_map<int, int>&, const int&);
static void dequeue_data_con(std::tr1::unordered_map<int, int>& d_c, const int& sock);
static void enqueue_client(std::queue<int>&, const int&);
static int get_next_client(std::queue<int>&);
std::string process_request(char* p_cmd, FTPClient& client, 
        const int& type, const int& sockfd) throw();
std::string byte2std(const int& size);

/* For the future */
static void client_conn_process();
static void client_req_process();
static void client_fin_process();

#endif /* FTP_FUNC_H */

