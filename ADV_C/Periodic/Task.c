#include <stdlib.h> /* malloc */

#include "Task.h"

#define MAGIC 0xDADBABAC
#define IS_TASK(T) ((T) && ((T)->m_magic) == MAGIC)


struct Task
{
	unsigned int    m_magic;
	TaskFunction    m_task;
	void*           m_context;
	Time*           m_nextTime;
	Time*           m_interval;
};

Task* TaskCreate(TaskFunction _taskFunction, void* _context, int _period_ms, const clockid_t _clockID)
{
    /* declarations */
    Task* task;
    
    /* checks */
    if(NULL == _taskFunction)
    {
        return NULL;
    }
    
    /* allocate */
    task = malloc(sizeof(Task));
    if(NULL == task)
    {
        return NULL;
    }
    
    /* initial task params*/
    task->m_nextTime = TimeCreateCurrent(_clockID);
    if(NULL == task->m_nextTime)
    {
        free(task);
        return NULL;
    }
    task->m_interval = TimeCreate(_period_ms);


    task->m_magic = MAGIC;
    task->m_task = _taskFunction;
    task->m_context = _context;
    
    return task;
}

void TaskDestroy(Task* _task)
{
    /* check */
    if(!IS_TASK(_task))
    {
        return;
    }
    
    /* destroy time */
    TimeDestroy(_task->m_nextTime);
    
    /* zero magic */
    _task->m_magic = 0;
    
    /* free task*/
    free(_task);
}

void TaskCalculateNext(Task* _task)
{
    if(!IS_TASK(_task))
    {
        return;
    }
    
    TimeAdd(_task->m_nextTime, _task->m_interval);
}

int TaskExecute(Task* _task)
{
    if(!IS_TASK(_task))
    {
        return 0;
    }
    
    TimeSleepUntil(_task->m_nextTime);
/*    _task->m_task(_task->m_context);*/
    
    return _task->m_task(_task->m_context);
}

int	TaskCompare(Task* _taskOne, Task* _taskTwo)
{
    if(!IS_TASK(_taskOne) || !IS_TASK(_taskTwo))
    {
        return -1;
    } 
    
    return TimeCompare(_taskOne->m_nextTime, _taskTwo->m_nextTime);
}


