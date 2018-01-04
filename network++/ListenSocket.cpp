#include <sys/socket.h>
//#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
//#include <algorithm>
#include <string.h>


#include "ListenSocket.h"

namespace network
{

ListenSocket::ListenSocket(unsigned short _port)
{
    if((m_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw std::runtime_error("SOCKET failed");
    }
    
    int opt = 1;
    if(setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        close(m_socket);
        throw std::runtime_error("SETSOCKOPT failed");
    }
    
    memset(&m_sockAddr, 0, sizeof(m_sockAddr));   // TODO replace with std::fill
    m_sockAddr.sin_family = AF_INET;
    m_sockAddr.sin_port = htons(_port);
    m_sockAddr.sin_addr.s_addr = INADDR_ANY;
    
    FD_ZERO(&m_bs);
    FD_SET(m_socket, &m_bs);
    FD_SET(0, &m_bs);
    
    if(bind(m_socket, (struct sockaddr*)&m_sockAddr, sizeof(struct sockaddr_in)) < 0)
    {
        close(m_socket);
        throw std::runtime_error("BIND failed");
    }
    
    if(listen(m_socket, 32) < 0)
    {
        close(m_socket);
        throw std::runtime_error("LISTEN failed");
    }
    m_isOpen = true;
}

ListenSocket::~ListenSocket()
{
    if(m_isOpen)
    {
        close(m_socket);
    }
}

}   //  namespace network
