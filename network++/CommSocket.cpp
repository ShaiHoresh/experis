#include <stdexcept>

#include "CommSocket.h"
#include "Message.h"

namespace network
{

CommSocket::~CommSocket()
{}

int CommSocket::Send(const Message& _msg)
{
	int ret = send(m_socket, _msg.m_data, _msg.m_size, MSG_NOSIGNAL);
	if(0 > ret)
	{
		throw std::runtime_error("SEND failed");		
	}
	return ret;
}

std::tr1::shared_ptr<Message> CommSocket::Receive(std::size_t _size)
{
	std::tr1::shared_ptr<Message> ret(new Message(_size));
	
	int read_bytes = recv(m_socket, ret->m_data, _size, 0);	
	if(read_bytes == 0)
	{
		throw std::runtime_error("CONNECTION LOST");
	}		
	if(read_bytes < 0)
	{
		throw std::runtime_error("RECEIVE failed");
	}
    
}

}  //  namespace network






