#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <stdint.h>     /*  uint16_t  */
#include <unistd.h>     /*  ssize_t   */
#include "List.h"


typedef struct Server Server;

typedef int (*UserFunc)(char*, ssize_t*, char*, size_t*);

int ServerRun(Server* _server);

Server* CreateServer(UserFunc _cb, uint16_t _port);

/*int AcceptClients(Server* _server);*/

/*int TreatRequest(Server* _server, fd_set _set, int activity);*/

void ServerDestroy(Server* _server);

#endif /* __TCP_SERVER_H__ */

