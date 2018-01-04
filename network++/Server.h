#ifndef __SERVER_H__
#define __SERVER_H__

#include "ListenSocket.h"


namespace network
{

class Server
{
public:
    explicit Server(unsigned short _port, unsigned short _qSize);
    ~Server();

    void Run();

private:
    unsigned short m_qSize;
    ListenSocket m_listener;
};




}   //  namespace network


#endif /* __SERVER_H__ */

