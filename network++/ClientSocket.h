#ifndef __CLIENT_SOCKET_H__
#define __CLIENT_SOCKET_H__

#include "CommSocket.h"


namespace network
{

class ClientSocket: public CommSocket
{
public:
    explicit ClientSocket(const std::string& _ip, unsigned short _port);    // connect
    ~ClientSocket();            // close

private:
    std::string m_ip;
    unsigned short m_port;    
};

}   // namespace network

#endif /* __CLIENT_SOCKET_H__ */

