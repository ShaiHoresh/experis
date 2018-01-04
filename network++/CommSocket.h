#ifndef __COMM_SOCKET_H__
#define __COMM_SOCKET_H__

#include <tr1/memory>

#include "Socket.h"

namespace network
{

class Message;

class CommSocket: public Socket
{
public:
     virtual ~CommSocket() = 0;
     
    int Send(const Message&);
    std::tr1::shared_ptr<Message> Receive(std::size_t);

private:
    
};

}   // namespace network

#endif /* __COMM_SOCKET_H__ */

