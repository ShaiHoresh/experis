#include <stdlib.h> /* atoi, abort*/
#include <string.h> /* strlen */
#include <unistd.h> /* getpid, write */
#include <stdio.h> /* sprintf, perror */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "MessageQ.h"

int ParseOptions(Params* _par, int argc, char **argv)
{
    int w;
    char info[] = "use flags: -c [create MQ], -d [delete MQ], -n [num of messages], -e [eof message/type], -v [verbosity], -s [speed] -f [file name]";
    
    while((w = getopt(argc, argv, "c:d:n:e:f:s:v:")) != -1)
    {
        switch(w)
        {
            case 'c':
                _par->m_create = atoi(optarg);
                break;
            case 'd':
                _par->m_delete = atoi(optarg);
                break;
            case 'e':
                _par->m_eof = (char)atoi(optarg);
                break;
            case 'n':
                _par->m_numOfCycles = (size_t)atoi(optarg);
                break;
            case 'f':
                strcpy(_par->m_file, optarg);
                break;
            case 's':
                _par->m_speed = (size_t)atoi(optarg);
                break;
            case 'v':
                _par->m_verbosity = (size_t)atoi(optarg);
                break;
            case '?':
                write(STDOUT_FILENO, info, strlen(info)); 
            default:
                abort();
        }
    }
    
    return 1;
}

int EstablishMessageQueue(Params* _par)
{
    key_t key;
    int msgQID;
    
    key = ftok(_par->m_file, ID);
    if(-1 == key)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    printf("%d\n", key);
    
    /*msgget*/
    if(_par->m_create == 0)
    {
        _par->m_create = IPC_CREAT;
    }
    
    msgQID = msgget(key, 0666 | _par->m_create);
    if(-1 == msgQID)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    
    return msgQID;
}

void WriteAndSendMessage(MsgStruct* _msgStruct, int _msgQID, long _type)
{
    int snd;
    
    _msgStruct->m_type = _type;
    _msgStruct->info.m_senderPid = getpid();
    
    sprintf(_msgStruct->info.m_text, "pid of sender: %u\n", _msgStruct->info.m_senderPid);
    
    snd = msgsnd(_msgQID, _msgStruct, sizeof(_msgStruct->info), 2);
    if(-1 == snd)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}

int RecieveMessage(MsgStruct* _msgStruct, int _msgQID, long _type)
{
    ssize_t rcv;
    rcv = msgrcv(_msgQID, _msgStruct, sizeof(_msgStruct->info), _type, 0); 
    if(-1 == rcv)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    
    if(_msgStruct->m_type == 3 || strcmp(_msgStruct->info.m_text, "close me") == 0)
    {
        return -1;
    }
    
    return 0;
}

void PrintMessage(MsgStruct* _msgStruct)
{
    write(STDOUT_FILENO, _msgStruct->info.m_text, strlen(_msgStruct->info.m_text));
    write(STDOUT_FILENO, "\n", 1);
}














