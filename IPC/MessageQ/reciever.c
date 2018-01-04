#include <unistd.h> /* getpid, write */
#include <stdlib.h> /* atoi, abort*/
#include <string.h> /* strlen */
#include <stdio.h> /* sprintf, perror */
#include <errno.h>

#include "MessageQ.h"




int main(int argc, char **argv)
{
    MsgStruct msgStruct;
    int msgQID = 0, key, timer = 10, ret, ctl;
    Params par = {0, 0, 1, 10, 200000, 1, PATH};
    
    ParseOptions(&par, argc, argv);
    
    
    key = ftok(par.m_file, ID);
    if(-1 == key) 
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    printf("%d\n", key);

    msgQID = msgget(key, 0);
    while(/*timer < 5000000 || */(msgQID == -1 && errno == ENOENT))
    {
        msgQID = msgget(key, 0);
       /* usleep(timer);
        timer *= 2;
        if(msgQID == 0) break;*/
    }
    
    for(;;)
    {
        sleep(1);
        
        ret = RecieveMessage(&msgStruct, msgQID, -3);
        if(ret == -1)
        {
            ctl = msgctl(msgQID, IPC_RMID, NULL);
            if(-1 == ctl)
            {
                perror("msgctl");
                exit(EXIT_FAILURE);
            }
        }
/****************************************        
        PrintOrDie()
****************************************/ 
        PrintMessage(&msgStruct);
                
        WriteAndSendMessage(&msgStruct, msgQID, 2);
    }
    return 0;
}

