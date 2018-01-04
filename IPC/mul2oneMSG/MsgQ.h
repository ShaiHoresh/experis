#ifndef __MSGQ_H__
#define __MSGQ_H__


typedef struct MsgStruct
{
    long    m_type;
    struct MsgInfo
    {
        pid_t   m_senderPid;
        char    m_text[256];
    }info;
} MsgStruct;

typedef struct Params
{
    int     m_create;
    int     m_delete;
    size_t  m_numOfCycles;
    size_t  m_speed;
    size_t  m_verbosity;
    char    m_file[256];
}Params;

/* channels of communication */
#define SERVER 2
#define CLIENTS 1

/* path */
#define PATH "/home/shai/Desktop/work/IPC/mul2oneMSG"

/* name of semaphore */
#define SEM_NAME "SemName"

int ParseOptions(Params* _par, int argc, char **argv);

int EstablishMessageQueue(Params* _par);

int ConnectMessagQueue(Params* _par);

void InitialMsgStruct(MsgStruct* _msgStruct);

void SendMessage(MsgStruct* _msgStruct, int _msgQID);

pid_t RecieveMessage(MsgStruct* _msgStruct, int _msgQID, long _type, int _flags);

void ReturnMessage(MsgStruct* _msgStruct, int _msgQID);

void PrintMessage(MsgStruct* _msgStruct);

#endif /* __MSGQ_H__ */
