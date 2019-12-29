/*************************************************************************
	> File Name: tcp_client.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年12月15日 星期日 23时25分55秒
 ************************************************************************/

#include<iostream>
#include<string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "tcp_client.h"

using namespace std;

#define PRT(format, arg...)  printf ("%s:%d   " format ,__func__, __LINE__, ##arg)
#define ERR(format, arg...)  printf ("%s:%d   err:" format ,__func__, __LINE__, ##arg)
#define DBG(format, arg...)  printf ("%s:%d   dbg:" format ,__func__, __LINE__, ##arg)
//#define DBG(format, arg...)  


string echo()
{
    return "tcp client";
}

int connect_timeout(int fd, struct sockaddr_in* addr, int timeout)
{
    int err = 0;
    if (fd < 0 || !addr)
    {
        ERR("param fd < 0\n");
        return -1;
    }
    /* block mode */
    if (timeout < 0)
    {
        err = connect (fd, (struct sockaddr*)addr, sizeof(struct sockaddr_in));
        if ( err < 0 )
        {
            ERR("connect() returned error: %s\n", strerror(err));
            return -1;
        }
        DBG("connect server success\n");
        return 0;
    }
    /* unblock mode */
    unsigned long  opt = 1;
    err = ioctl(fd, FIONBIO, &opt);
    if (err != 0)
    {
        ERR("ioctl() returned error: %s\n", strerror(err));
        return -1;
    }
    err = connect (fd, (struct sockaddr*)addr, sizeof(struct sockaddr_in));
    if (err < 0)
    {
        if(errno == EINPROGRESS)
        {
            struct timeval tm;
            fd_set set;
            int error = -1;
            int len = sizeof(error);
            tm.tv_sec = timeout;
            tm.tv_usec = 0;

            FD_ZERO(&set);
            FD_SET(fd, &set);
            if(select(fd+1, NULL, &set, NULL, &tm) > 0)
            {
                getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len);
                err = (error==0)?0:-1;
            }
            else
            {
                err = -1;
            }
        }
        else
        {
            err = -1;
        }
    }
    opt = 0;
    ioctl(fd, FIONBIO, &opt);
    return err;
}

/*
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
*/
client::client()
{
    m_port = 0;
    m_fd = -1;
}
client::~client()
{

}


int client::cli_init()
{
    DBG("start\n");
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0){
        ERR("socket create err\n");
        return -1;
    }
    m_fd = fd;
    DBG("end\n");
    return 0;
}

int client::cli_connect(string &ip, unsigned short port)
{
    DBG("start\n");
    int ret;
    if (m_fd < 0){
        ERR("fd is illagel, init first\n");
        return -1;
    }
    m_ip = ip;
    m_port = port;
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    ret = inet_pton(AF_INET, ip.c_str(), &saddr.sin_addr);
    if (ret != 1){
        ERR("the ip is illagel\n");
        return -1;
    }
    int addrlen = sizeof (saddr);
   
    ret = connect_timeout(m_fd, &saddr, 10);
    if (ret != 0){
        return -1;
    }
    DBG("end\n");
    return 0;
}

int client::cli_connect(string &url)
{
    DBG("start\n");
    m_url = url;


    DBG("end\n");
    return 0;
}
int client::cli_send(void* data, int len)
{
    DBG("start\n");
    if (!data || len <= 0){
        ERR("data null, or len less than 0\n");
        return -1;
    }

    if (m_fd < 0){
        ERR("fd less than 0\n");
        return -1;
    }
    int ret, num;
    num = send (m_fd, data, len, 0);
    DBG("send %d\n", num);
    DBG("end\n");
    return num;
}

int client::cli_recv(void* data, int len)
{
    DBG("start\n");
    if (!data || len <= 0){
        ERR("data null, or len less than 0\n");
        return -1;
    }
    if (m_fd < 0){
        ERR("fd less than 0\n");
        return -1;
    }
    
    int num = 0;
    num = recv(m_fd, data, len, 0);
    DBG("recv %d\n", num);
    DBG("end\n");
    return num;
}

int client::cli_close()
{
    DBG("start\n");
    if (m_fd < 0)
    {
        ERR("fd less than 0\n");
        return -1;
    }
    close(m_fd);
    m_fd = -1;
    m_port = 0;
    DBG("end\n");
    return 0;
}
