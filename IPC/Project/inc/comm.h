#ifndef __COMM_H__
#define __COMM_H__

#include "pdu.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct CommData
{
    key_t   m_key;
    int     m_flags;
    int     m_id;
    char    m_path[64];
    int     m_type;
};

typedef struct CommData CommData;

CommData* CommCreate();

int CommConnect(CommData* _comm);

/**
 * returns 0 for success!!!
*/
int PushData(CommData* _comm, CDRData* _context);

int PullData(CommData* _comm, CDRData* _context);

void CommClose(CommData* _comm);

#endif /* #ifndef __COMM_H__ */


