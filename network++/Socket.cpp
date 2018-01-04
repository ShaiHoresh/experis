#include <fcntl.h>
#include <stdexcept>

#include "Socket.h"

namespace network
{

Socket::Socket()
: m_socket(0)
, m_isblocked(false)
, m_isOpen(false)
{}

Socket::~Socket()
{}

void Socket::Block (bool _blocking)
{
    int flags, ret;
    if(-1 == (flags = fcntl(m_socket, F_GETFL)))
	{
		throw std::runtime_error("FCNTL failed");
	}
	
	if(m_isblocked)
	{
	    ret == fcntl(m_socket, F_SETFL, flags | (~O_NONBLOCK));
	}
	else
	{
        ret == fcntl(m_socket, F_SETFL, flags | O_NONBLOCK);
	}
	
	if(-1 == ret)
	{
	    throw std::runtime_error("FCNTL failed");
	}
}


} // network
