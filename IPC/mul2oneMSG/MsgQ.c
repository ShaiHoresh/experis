#include <stdlib.h> /* atoi, abort*/
#include <string.h> /* strlen */
#include <unistd.h> /* getpid, write */
#include <stdio.h> /* sprintf, perror */
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "MsgQ.h"

/*check what flags are needed*/
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

/* server */
int EstablishMessageQueue(Params* _par)
{
    key_t key;
    int msgQID;
    
    key = ftok(_par->m_file, 'p');
    if(-1 == key)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    printf("%d\n", key);
    
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

/* client */
int ConnectMessagQueue(Params* _par)
{
    key_t key;
    int msgQID;
    
    key = ftok(_par->m_file, 'p');
    if(-1 == key)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    printf("%d\n", key);
        
    msgQID = msgget(key, 0);
    if(-1 == msgQID)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    return msgQID;
}

/* client side only!! */
void SendMessage(MsgStruct* _msgStruct, int _msgQID)
{
    ssize_t snd;
    
    snd = msgsnd(_msgQID, _msgStruct, sizeof(_msgStruct->info), 0);
    if(-1 == snd)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("sending message: %s", _msgStruct->info.m_text);
}

/* server side */
void ReturnMessage(MsgStruct* _msgStruct, int _msgQID)
{
    int snd;
    
    strcpy(_msgStruct->info.m_text, "coming back from server\n");
    
    _msgStruct->m_type = SERVER;
    snd = msgsnd(_msgQID, _msgStruct, sizeof(_msgStruct->info), 0);
    if(-1 == snd)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}

/* both server and client */
pid_t RecieveMessage(MsgStruct* _msgStruct, int _msgQID, long _type, int _flags)
{
    ssize_t rcv;
    rcv = msgrcv(_msgQID, _msgStruct, sizeof(_msgStruct->info), _type, _flags); 
    if(-1 == rcv && errno != ENOMSG)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    if(errno == ENOMSG)
    {
        _msgStruct->info.m_senderPid = 0;
    }
    
 /*   printf("received message: %s", _msgStruct->info.m_text);*/
    return _msgStruct->info.m_senderPid;
}

void InitialMsgStruct(MsgStruct* _msgStruct)
{
    _msgStruct->m_type = CLIENTS;
    _msgStruct->info.m_senderPid = getpid();
    sprintf(_msgStruct->info.m_text, "pid of sender: %u\n", _msgStruct->info.m_senderPid);
}

void PrintMessage(MsgStruct* _msgStruct)
{
    write(STDOUT_FILENO, _msgStruct->info.m_text, strlen(_msgStruct->info.m_text));
    write(STDOUT_FILENO, "\n", 1);
}


























