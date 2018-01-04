#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <stddef.h>
#include "List.h"


typedef struct Server Server;

typedef int (*UserFunc)(char*, size_t*, char*, size_t*);

Server* CreateServer(UserFunc _cb, int _port);

int AcceptClients(Server* _server);

int TreatRequest(Server* _server);

void ServerDestroy(Server* _server);

#endif /* __TCP_SERVER_H__ */

