/*#include <sys/socket.h>*/
/*#include <sys/types.h>*/
/*#include <netinet/in.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "comm.h"


int OpenSocket()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();
    }
    return sock;
}

void InitServer(struct sockaddr_in* sin, unsigned short port)
{
    memset(sin, 0, sizeof(struct sockaddr_in));
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = INADDR_ANY;
}

void InitClient(struct sockaddr_in* sin, unsigned short port, char* ip)
{
    memset(sin, 0, sizeof(struct sockaddr_in));
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = inet_addr(ip);
}

void Bind(int* sock, struct sockaddr_in* sin)
{
    if(bind(*sock, (struct sockaddr*)sin, sizeof(struct sockaddr_in)) == -1)
    {
        perror("bind failed");
        abort();
    }
}

ssize_t Receive(int* sock, struct sockaddr_in* sin)
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

ssize_t Send(int* sock, struct sockaddr_in* sin)
{
    ssize_t snd;
    char buffer[1024];
    socklen_t sndLen;
    
    scanf("%s", buffer);
    sndLen = sizeof(*sin);
    snd = sendto(*sock, &buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)sin, sndLen);
    if(snd < sndLen)
    {
        perror("message cut");
    }
    
    return snd;
}
