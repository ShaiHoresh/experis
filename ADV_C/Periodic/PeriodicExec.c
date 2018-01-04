

#include "Scheduler.h"


struct PeriodicExecutor
{
	PriorityQueue*  m_priorityQ;
	size_t          m_runCycles;
	int             m_pauseRequest;
	const char[32]  m_name;
	clockid_t       m_clockID;
};
/*
static function to implement:
PQCreate

*/
PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t ​_clockID)
{
    PeriodicExecutor* pe;
    
    pe = malloc(sizeof(PeriodicExecutor));
    if(NULL == pe)
    {
        return NULL;
    }
    
    pe->m_priorityQ = PQCreate(); /* TODO implement */
    if(NULL == pe->m_priorityQ)
    {
        free(pe);
        return NULL;
    }
    
    
    if(_name != NULL)
    {
        pe->m_name = _name;
    }
    pe->m_clockID = _clockID;
    pe->m_runCycles = 0;
    pe->m_pauseRequest = 0;
    
    return pe;
}

void PeriodicExecutorDestroy(PeriodicExecutor* _executor)
{
    
}















