/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   start.cc
 * Author: Seven
 *
 * Created on August 8, 2016, 9:09 PM
 */

#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

extern ftp_server_start();

string user, pswd;

string get_user_name()
{
    return user;
}

string get_password()
{
    return pswd;
}

int main(int argc, char** argv)
{
    cout << "Input Local Database User Name: ";
    cin >> user;
    pswd = getpass("Password: ");
    ftp_server_start();
    
    return 0;
}

