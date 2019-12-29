/*************************************************************************
	> File Name: tcp_cli_app.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年12月29日 星期日 12时30分15秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <tcp_client.h>

#include<iostream>

using namespace std;



#define PRT(format, arg...)  printf ("%s:%d   " format ,__func__, __LINE__, ##arg)
#define ERR(format, arg...)  printf ("%s:%d   err:" format ,__func__, __LINE__, ##arg)
#define DBG(format, arg...)  printf ("%s:%d   dbg:" format ,__func__, __LINE__, ##arg)

static void* recv_from_net(void * agrv);

void usage()
{
    printf ("usage:\n\t");
    printf ("./tcp_cli_app -I 192.168.0.106 -p 50000\n");
}

int main (int argc, char** argv)
{
    char ch;
    char ip[32];
    unsigned short port = 0;
    printf ("A tcp client demo\n");

    memset(ip, 0, sizeof(ip));
    while ((ch = getopt(argc, argv, "p:I:")) != -1)
    {
        switch(ch)
        {
            case 'p':
            {
                port = atoi(optarg);
            }
            break;
            case 'I':
            {
                strncpy(ip, optarg, sizeof(ip)-1);
            }
            break;
            case '?':
            {
                ERR (" get a ?\n");
            }
            break;
            case ':':
            {
                ERR (" get a :\n");
            }
            break;
            default:
            {
                ERR (" get a unknow\n");
            }
            break;
        }
    }

    printf ("server ip:%s  port:%d\n", ip, port);
    if (ip[0] == '\0' || port == 0){
        usage();
        exit(0);
    }
    int ret;

    client* cli = new client();

    cli->cli_init();
    string str_ip = ip;
    ret = cli->cli_connect(str_ip, port);
    if (ret < 0){
        ERR("connect server failed\n");
        return -1;
    }
    
    pthread_t tid;
    char buf[1024];
    ret = pthread_create (&tid, NULL, recv_from_net, (void*)cli);
    if (ret != 0)
    {
        ERR("create pthread failed\n");
        return -1;
    }

    for ( ; ; )
    {
        scanf("%s", buf);

        //printf ("%s\n", buf);

        ret = cli->cli_send(buf, strlen(buf)+1);
        if (ret <= 0){
            ERR("send error\n");
            break;
        }
    }

    cli->cli_close();
    delete cli;
    cli = NULL;
    
    PRT ("demo exit\n");
    return 0;
}



static void* recv_from_net(void * argv)
{
    if (!argv){
        ERR("argv null\n");
        exit(1);
    }

    client* cli = (client*)argv;
    if (cli < 0){
        ERR("fd less than 0\n");
        exit(1);
    }
    char buf[1024];
    int ret = 0;
    for ( ; ; )
    {
        ret = cli->cli_recv(buf, sizeof(buf)-1);
        if (ret > 0){
            buf[ret] = '\0';
            printf ("resv:%d :%s\n", ret, buf);
        }
        if (ret == 0)
        {
            PRT("connetc close\n");
            break;
        }
        else if (ret < 0){
            ERR("read err, connect close\n");
            break;
        } 
    }
    exit (1);
}
