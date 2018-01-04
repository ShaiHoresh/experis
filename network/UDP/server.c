#include <unistd.h>
#include <stdlib.h>

#include "comm6.h"

int main (int argc, char *argv[])
{
    int sock;
    unsigned int i;
    unsigned short port;
    sockaddr sin;
    
    port = (unsigned short)atoi(argv[1]);
    
    sock = OpenSocket();
    InitServer(&sin, port);
    Bind(&sock, &sin);

    for (i = 0; i < 2; ++i)
    {
        Receive(&sock, &sin);
        Send(&sock, &sin);
    }

    close(sock);

    return 0;
}
