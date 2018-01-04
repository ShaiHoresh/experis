#ifndef __COMMUNICATION6_H__
#define __COMMUNICATION6_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

typedef struct sockaddr_in6 Sockaddr;

int OpenSocket();

void InitServer(Sockaddr* sin, unsigned short port);

void InitClient(Sockaddr* sin, unsigned short port, char* ip);

void Bind(int* sock, Sockaddr* sin);

ssize_t Receive(int* sock, Sockaddr* sin);

ssize_t Send(int* sock, Sockaddr* sin);


#endif /* __COMMUNICATION6_H__ */
