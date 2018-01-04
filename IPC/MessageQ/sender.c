#include <unistd.h> /* getpid, write */
#include <stdlib.h> /* atoi, abort*/
#include <string.h> /* strlen */
#include <stdio.h> /* sprintf, perror */

#include "MessageQ.h"

int SendKillerMessageAndDie(char _eof, int _msgQID, MsgStruct* _msgStruct);

int main(int argc, char **argv)
{
    int msgQID, i;
    MsgStruct msgStruct;
    Params par = {0, 0, 1, 10, 1000000, 1, PATH};
    
    ParseOptions(&par, argc, argv);
    
    msgQID = EstablishMessageQueue(&par);
    
    for(i = 0; i < par.m_numOfCycles; ++i)
    {
        WriteAndSendMessage(&msgStruct, msgQID, 1);
        usleep(par.m_speed);
        RecieveMessage(&msgStruct, msgQID, -3);
        PrintMessage(&msgStruct);
    }
    
    sleep(3);
    
    SendKillerMessageAndDie(par.m_eof, msgQID, &msgStruct);
    
    return 0;
}


int SendKillerMessageAndDie(char _eof, int _msgQID, MsgStruct* _msgStruct)
{
    char message[] = "close me";
    size_t size;
    int snd;
    ssize_t ctl;
    if(1 == MSG)
    {
        _msgStruct->info.m_text[0] = message[0];
    }
    else
    {
        _msgStruct->m_type = 3;
    }
    _msgStruct->info.m_senderPid = getpid();
    
    size = strlen(message);
    snd = msgsnd(_msgQID, _msgStruct, size + 1, (int)_msgStruct->m_type);
    if(-1 == snd)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    
    ctl = msgctl(_msgQID, IPC_RMID, NULL);
    if(-1 == ctl)
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}




