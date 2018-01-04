#ifndef __SOCKET_T_H__
#define __SOC__SOCKET_T_H__KET_H__

#include <sys/socket.h>

namespace network
{

class Socket_t
{
public:
    // using default ctor, dtor & copy assignment op
    Socket_t(int);
    operator int() const;
    
private:
    int m_sock;
};

inline Socket_t::operator int() const
{
    return m_sock;
}

}   //  namespace network

#endif /* __SOCKET_T_H__ */

