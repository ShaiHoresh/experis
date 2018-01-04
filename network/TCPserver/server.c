#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "comm.h"

int ReturnMessage(char* _strIn, size_t* _lenIn, char* _strOut, size_t* _lenOut)
{
	char* buf = "Hi client. How are you??";
	
	printf("%s\n", _strIn);
	
	*_lenOut = strlen(buf);
	strcpy(_strOut, buf);
	
	return 0;
}

int main (int argc, char *argv[])
{
    Server* server;
    unsigned short port;
    
    port = (unsigned short)atoi(argv[1]);
    
    server = CreateServer(ReturnMessage, port);
    
    for(;;)
    {
        while(AcceptClients(server));
        TreatRequest(server);
    }
    
    ServerDestroy(server);
    
    return 0;
}
