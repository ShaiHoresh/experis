#include <time.h>

#include <stdlib.h>
#include <string.h>
#include "../../inc/Scheduler.h"
#include "Task.h"

#define MAGIC 0xDCBACBAD
#define TRUE 1
#define FALSE 0
#define IS_EXECUTOR(E) ((E) && (E)->m_magic == MAGIC)

struct PeriodicExecutor
{
    unsigned int    m_magic;
    PriorityQueue*  m_priorityQ;
    size_t          m_runCycles;
    int             m_pauseRequest;
    char            m_name[64];
    clockid_t       m_clockID;
};

PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clockID)
{
    PeriodicExecutor* executor;
    Vector* vector;
    
    executor = malloc(sizeof(PeriodicExecutor));
    if(NULL == executor)
    {
        return NULL;
    }
    vector = VectorCreate(10, 5);
    if(NULL == vector)
    {
        return NULL;
    }
    
    executor->m_priorityQ = HeapBuild(vector, (LessThanComparator)TaskCompare);
    if(NULL == executor->m_priorityQ)
    {
        return NULL;
    }
    
    executor->m_magic = MAGIC;
    executor->m_runCycles = 0;
    executor->m_pauseRequest = 0;
    strcpy(executor->m_name, _name);
    executor->m_clockID = _clockID;
    
    return executor;
}


void PeriodicExecutorDestroy(PeriodicExecutor* _executor)
{
    Vector* vector;
    if(IS_EXECUTOR(_executor))
    {
        return;
    }
  /*  HeapForEach(_executor->m_priorityQ, TaskDestroy, NULL);*/
    vector = HeapDestroy(&(_executor->m_priorityQ));
    VectorDestroy(&vector, TaskDestroy);
    _executor->m_magic = 0;
    free(_executor);
    
    return;
}

/**
 */
int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunction _task, void* _context, int _period_ms)
{
    Task* task;
    HeapResult error;
    
    if(!IS_EXECUTOR(_executor))
    {
        return FALSE;
    }
    
    task = TaskCreate(_task, _context, _period_ms, _executor->m_clockID);
    TaskCalculateNext(task);
    error = HeapInsert(_executor->m_priorityQ, task);
    if(error != 0)
    {
        return FALSE;
    }
    return TRUE;
}

size_t PeriodicExecutorRun(PeriodicExecutor* _executor)
{
    /*dec*/
    Task* task;
    int res;

    /*check*/
    if(!IS_EXECUTOR(_executor))
    {
        return 0;
    }
    /*task execute in loop - check if heap is empty or flag is up*/
    while(NULL != (task = HeapExtract(_executor->m_priorityQ)))
    {
        res = TaskExecute(task);
        _executor->m_runCycles++;
        if(1 == _executor->m_pauseRequest)
        {
            break;
        }
        TaskCalculateNext(task);
        if(res)
        {
            HeapInsert(_executor->m_priorityQ, task);
        }
    }
    return _executor->m_runCycles;
}

size_t PeriodicExecutorPause(PeriodicExecutor* _executor)
{
    if(!IS_EXECUTOR(_executor))
    {
        return 0;
    }
    
    _executor->m_pauseRequest = 1;
    
    return HeapSize(_executor->m_priorityQ);
}









