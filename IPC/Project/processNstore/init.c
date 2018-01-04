#include <stdlib.h>

/*#include "init.h"*/
#include "comm.h"
#include "processor.h"
#include "subsStorage.h"
#include "operStorage.h"

#define MAGIC 0xEFCABCBC

struct Processor
{
    unsigned int    m_magic;
    SubsDS*         m_subs;
    OperDS*         m_oper;
    CommData*       m_comm;
};

typedef struct Processor Processor;

Processor* ProcessorCreate()
{
    /*dec*/
    Processor* processor;
    
    /*check?!*/
    /*malloc*/
    processor = malloc(sizeof(Processor));
    if(!processor)
    {
        return NULL;
    }
    
    /*init*/
    processor->m_subs = SubsDSCreate();
    if(!processor->m_subs)
    {
        free(processor);
        return NULL;
    }
    
    processor->m_oper = OperDSCreate();
    if(!processor->m_oper)
    {
        SubsDestroyDS(processor->m_subs);
          free(processor);
    }
    
    processor->m_comm = CommCreate();
    if(!processor->m_comm)
    {
        SubsDestroyDS(processor->m_subs);
        OperDestroyDS(processor->m_oper);
        free(processor);
    }
    
    processor->m_magic = MAGIC;
    
    /*return*/
    return processor;
}

void ProcessorDestroy(Processor* _processor)
{
    if(_processor && _processor->m_magic == MAGIC)
    {
        _processor->m_magic = 0;
        SubsDestroyDS(_processor->m_subs);
        OperDestroyDS(_processor->m_oper);
        CommClose(_processor->m_comm);
        free(_processor);
    }
}
