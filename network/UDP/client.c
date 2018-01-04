#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"

int main (int argc, char *argv[])
{
    int sock;
    unsigned int i;
    unsigned short port;
    sockaddr sin;
    char channel[16];
    
    port = (unsigned short)atoi(argv[1]);
    strcpy(channel, argv[2]);
    
    sock = OpenSocket();
    InitClient(&sin, port, channel);
    
    for (i = 0; i < 2; ++i)
    {
        Send(&sock, &sin);
        Receive(&sock, &sin);
    }
    
    close(sock);

    return 0;
}
