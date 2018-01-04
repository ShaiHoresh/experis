/*#include <sys/socket.h>*/
/*#include <sys/types.h>*/
/*#include <netinet/in.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "comm6.h"


int OpenSocket()
{
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();
    }
/*    printf("%d\n", sock);*/
    return sock;
}

void InitServer(Sockaddr* sin, unsigned short port)
{
    memset(sin, 0, sizeof(*sin));
    sin->sin6_family = AF_INET6;
    sin->sin6_port = htons(port);
    sin->sin6_addr = in6addr_any;
}

void InitClient(Sockaddr* sin, unsigned short port, char* ip)
{
    memset(sin, 0, sizeof(*sin));
    sin->sin6_family = AF_INET6;
    sin->sin6_port = htons(port);
    strcpy(sin->sin6_addr.s6_addr, ip);
}

void Bind(int* sock, Sockaddr* sin)
{
    if(bind(*sock, (struct sockaddr*)sin, sizeof(*sin)) == -1)
    {
        perror("bind failed");
        abort();
    }
}

ssize_t Receive(int* sock, Sockaddr* sin)
{
    unsigned int len;
    char buffer[1024];
    ssize_t rcv;
    
    len = sizeof(*sin);
    
    rcv = recvfrom(*sock, &buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)sin, &len);
    if(rcv < 0)
    {
        perror("receive failed");
    }
    else if(rcv > 0)
    {
        buffer[rcv] = '\0';
        printf("%s\n", buffer);
    }
    
    return rcv;
}

ssize_t Send(int* sock, Sockaddr* sin)
{
    ssize_t snd;
    char buffer[1024];
    socklen_t sndLen;
    
    scanf("%s", buffer);
    sndLen = sizeof(*sin);
    snd = (ssize_t)sendto(*sock, &buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)sin, sndLen);
    if(snd < sndLen)
    {
        perror("message cut");
    }
    
    return snd;
}
