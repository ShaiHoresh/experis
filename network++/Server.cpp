

#include "Server.h"
#include "ServerSocket.h"

namespace network
{


Server::Server(unsigned short _port, unsigned short _qSize)
: m_listener(_port)
, m_qSize(_qSize)
{}

Server::~Server()
{}

void Server::Run()
{

}




}   //  namespace network
