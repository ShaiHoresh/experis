#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H__

#include "CommSocket.h"
#include <arpa/inet.h>  // struct sockaddr_in
namespace network
{

class ServerSocket: public CommSocket
{
public:
    explicit ServerSocket(unsigned short _port);
     ~ServerSocket();

    // friend class ListenSocket;

private:

};

}   // namespace network

#endif // __SERVER_SOCKET_H__

