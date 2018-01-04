#ifndef __MESSAGE_Q__
#define __MESSAGE_Q__

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATH    "/home/shai/Desktop/work/IPC/MessageQ"
#define ID      5
#define MSG     1
#define TYPE    2

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
    char    m_eof;
    size_t  m_numOfCycles;
    size_t  m_speed;
    size_t  m_verbosity;
    char    m_file[256];
}Params;

int ParseOptions(Params* _par, int argc, char **argv);

int EstablishMessageQueue(Params* _par);

void WriteAndSendMessage(MsgStruct* _msgStruct, int _msgQID, long _type);

int RecieveMessage(MsgStruct* _msgStruct, int _msgQID, long _type);

void PrintMessage(MsgStruct* _msgStruct);

#endif /* __MESSAGE_Q__ */
