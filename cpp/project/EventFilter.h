#ifndef __EVENT_FILTER_H__
#define __EVENT_FILTER_H__

#include <pthread.h>
#include <tr1/memory>
#include "Pqueue.h"

class Controller;
class Agent;

class EventFilter
{
public:
    EventFilter(const Agent* _agent);
    virtual ~EventFilter();
    
    bool InsertToQueue(const std::tr1::shared_ptr<Event> _event);
    
    void GrindQueue();
    
private:
    static void* Trampoline(void*);
    SafeQueue<std::tr1::shared_ptr<Event> >* m_events;
    pthread_t m_thread;
    Agent* m_agent;
};

#endif /* __EVENT_FILTER_H__ */

