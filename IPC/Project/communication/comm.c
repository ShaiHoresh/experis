#include <stdlib.h> /* atoi, abort*/
#include <string.h> /* strlen */
#include <unistd.h> /* getpid, write */
#include <stdio.h> /* sprintf, perror */
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "comm.h"

/*#define _XOPEN_SOURCE 700*/
/*
struct CommData
{
    key_t   m_key;
    int     m_flags;
    int     m_id;
    char    m_path[64];
    int     m_type;
};
*/
typedef struct Data
{
    long    m_type;
    CDRData m_buffer;
}Data;

/*
typedef struct QData
{
    long    m_type;
    void*   m_data;
}QData;
*/

CommData* CommCreate(char* _conFileName)
{
    /*dec*/
    CommData* data;
    char fileName[16];
    
    /*check*/
    
    if (!_conFileName)
    {
        strcpy(fileName, "/etc/passwd");
    }
    else
    {
        strcpy(fileName, _conFileName);
    }
    
    /*malloc*/
    data = malloc(sizeof(CommData));
    if(!data)
    {
        return NULL;
    }
    
    /*init*/
    data->m_key = ftok(fileName, 'b');
    if(!data->m_key)
    {
        free(data);
        return NULL;
    }
    data->m_flags = 0666 | IPC_CREAT;
    data->m_type = 1;
    data->m_id = msgget(data->m_key, data->m_flags);
    if(-1 == data->m_id)
    {
        free(data);
        return NULL;
    }
    
    /*return*/
    return data;    
}

int PushData(CommData* _comm, CDRData* _context)
{
    int ret;
    Data data;
    
    if(!_comm || !_context)
    {
        return -1;
    }
    
    data.m_type = _comm->m_type;
    data.m_buffer = *_context;
    
    ret = msgsnd(_comm->m_id, &data, sizeof(data.m_buffer), 0);
    
    return ret;
}

int PullData(CommData* _comm, CDRData* _context)
{
    int ret;
    Data data;
    
    if(!_comm)
    {
        return -1;
    }
    
    ret = msgrcv(_comm->m_id, &data, sizeof(data.m_buffer), _comm->m_type, 0);
    
    if(-1 == ret)
    {
        return ret;
    }
    *_context = data.m_buffer;
    
    return 0;
}

void CommClose(CommData* _comm)
{
    if(!_comm)
    {
        return;
    }
    
    msgctl(_comm->m_id, IPC_RMID, NULL);
}
/*
int QuerySend(void* _data)
{
    data->m_key = ftok(fileName, 'b');
    if(!data->m_key)
    {
}
*/



