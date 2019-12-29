#ifndef TCP_CLIENT_H
#define  TCP_CLIENT_H


#include<iostream>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
using namespace std;


string echo();

int connect_timeout(int fd, struct sockaddr_in* addr, int timeout);

class client{

public:
    client();
    ~client();

public:
    int cli_init();
    int cli_connect(string &ip, unsigned short port);
    int cli_connect(string &url);
    int cli_send(void* data, int len);
    int cli_recv(void* data, int len);
    int cli_close();

private:
    
    string m_ip;
    unsigned short m_port;
    string m_url;
    int m_fd;
};

#endif
