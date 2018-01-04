#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"

int main (int argc, char *argv[])
{
    int sock, cli, i = 1000;
    struct sockaddr_in sin;
    char buffer[1024];
    char* message = "Server message\n";
    unsigned short port;
    
    port = (unsigned short)atoi(argv[1]);
    sock = OpenSocket();
    
    InitServer(&sock, &sin, port);
    cli = Accept(&sock, &sin);
    
    while(i--)
    {
        if(Receive(cli, buffer, sizeof(buffer)) > 0)
        {
            printf("I'm the server, and I've a message: %s", buffer);
        }
        
        Send(cli, message, strlen(message));
    }
    close(sock);
    
    return 0;
}
