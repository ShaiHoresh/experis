#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "comm.h"

int main (int argc, char *argv[])
{
    int sock, i = 1000;
    struct sockaddr_in sin;
    char buffer[1024];
    char* message = "shai's message";
    unsigned short port;
    char channel[16];

    strcpy(channel, argv[2]);
    port = (unsigned short)atoi(argv[1]);
    sock = OpenSocket();
    
    InitClient(&sin, port, channel);
    Connect(&sock, &sin);
    
    while(i--)
    {
        Send(sock, message, strlen(message));
        
        if(Receive(sock, buffer, sizeof(buffer)) > 0)
        {
            printf("I'm the client, and I've a message: %s", buffer);
        }
    }
    
    close(sock);
    
    return 0;
}

