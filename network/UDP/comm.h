#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include <netinet/in.h>
/*#include <sys/types.h>*/
typedef struct sockaddr_in sockaddr;

int OpenSocket();

void InitServer(struct sockaddr_in* sin, unsigned short port);

void InitClient(struct sockaddr_in* sin, unsigned short port, char* ip);
 
void Bind(int* sock, struct sockaddr_in* sin);

ssize_t Receive(int* sock, struct sockaddr_in* sin);

ssize_t Send(int* sock, struct sockaddr_in* sin);


#endif /* __COMMUNICATION_H__ */
