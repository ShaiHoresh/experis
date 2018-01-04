#include <string.h>
#include <stdio.h>
#include <stdlib.h>     /*  atoi  */


#include "comm.h"

int ReturnMessage(char* _strIn, ssize_t* _lenIn, char* _strOut, size_t* _lenOut)
{
	char* buf = "Hi client. How are you??";
	
	printf("%s\n", _strIn);
	
	*_lenOut = strlen(buf);
	strcpy(_strOut, buf);
	
	return 0;
}

int WelcomeMessage(char* _strOut, size_t* _lenOut)
{
	char* buf = "Welcome!";
	
	*_lenOut = strlen(buf);
	strcpy(_strOut, buf);
	
	return 0;
}

int main (int argc, char *argv[])
{
    Server* server;
    uint16_t port;
    
    port = (uint16_t)atoi(argv[1]);
    
    server = CreateServer(ReturnMessage, WelcomeMessage, port);
    
    ServerRun(server);

    ServerDestroy(server);
    
    return 0;
}
