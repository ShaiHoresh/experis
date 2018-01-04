#ifndef __Listening_SOCKET_H__
#define __Listening_SOCKET_H__

#include "Socket.h"
#include <arpa/inet.h>  // struct sockaddr_in
    
namespace network
{

class ListenSocket: public Socket
{
public:
    explicit ListenSocket(unsigned short _port); // socket, Init
     ~ListenSocket();              // close
     
private:
    fd_set m_bs;
    struct sockaddr_in m_sockAddr;
};

}   // namespace network

#endif /* __Listening_SOCKET_H__ */

