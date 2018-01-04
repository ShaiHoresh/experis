#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <tr1/memory>

#include "Socket_t.h"

namespace network
{

class Message;

class Socket
{
public:
    Socket ();
    virtual ~Socket () = 0;
    
    void Block (bool _blocking = true);
    Socket_t GetNativeSocket() const;

protected:
    Socket_t m_socket;
    bool m_isblocked;
    bool m_isOpen;
};

inline Socket_t Socket::GetNativeSocket() const
{
    return m_socket;
}

}   //  namespace network


#endif // __SOCKET_H__ 

