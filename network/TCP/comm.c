#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "comm.h"


int OpenSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();
    }
    return sock;
}

void InitServer(int* _sock, struct sockaddr_in* _sin, unsigned short _port)
{
    int opt = 1;
    
    if(setsockopt(*_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        printf("setsockopt failed\n");
    }
    
    memset(_sin, 0, sizeof(struct sockaddr_in));
    _sin->sin_family = AF_INET;
    _sin->sin_port = htons(_port);
    _sin->sin_addr.s_addr = INADDR_ANY;
    
    if(bind(*_sock, (struct sockaddr*)_sin, sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind failed");
        abort();
    }
    
    if(listen(*_sock, 5) < 0)
    {
        perror("listen failed");
        abort();
    }
}

void InitClient(struct sockaddr_in* sin, unsigned short port, char* ip)
{
    memset(sin, 0, sizeof(struct sockaddr_in));
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = inet_addr(ip);
}

void Connect(int* _sock, struct sockaddr_in* _sAdd)
{
    if(connect(*_sock, (struct sockaddr*)_sAdd, sizeof(struct sockaddr_in)) < 0)
    {
        perror("connect failed");
        abort();
    }
}

int Accept(int* _sock, struct sockaddr_in* _sAdd)
{
    int sock;
    unsigned int len;

    if((sock = accept(*_sock, (struct sockaddr*)_sAdd, &len)) < 0)
    {
        perror("accept failed");
        abort();
    }
    return sock;
}

ssize_t Send(int _sock, char* _buffer, size_t _len)
{
    ssize_t snd; 
    
    if((snd = send(_sock, _buffer, _len + 1, 0)) < 0)
    {
        perror("send failed");
        abort();
    }
    
    return snd;
}

ssize_t Receive(int _sock, char* _buffer, size_t _len)
{
    ssize_t rcv;
    
    if((rcv = recv(_sock, _buffer, _len - 1, 0)) < 0)
    {
        perror("receive failure");
        abort();
    }
    
    return rcv;
}




















