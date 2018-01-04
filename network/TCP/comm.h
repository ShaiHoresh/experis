#ifndef __TCP_COMM_H__
#define __TCP_COMM_H__

#include <netinet/in.h>

int OpenSocket();

void InitServer(int* _sock, struct sockaddr_in* sin, unsigned short port);

void InitClient(struct sockaddr_in* sin, unsigned short port, char* ip);

void Connect(int* _sock, struct sockaddr_in* sAdd);

int Accept(int* _sock, struct sockaddr_in* sAdd);

ssize_t Send(int _sock, char* _buffer, size_t _len);

ssize_t Receive(int _sock, char* _buffer, size_t _len);

#endif /* __TCP_COMM_H__ */


