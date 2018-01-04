#include <iostream>

#include "Event.h"
#include "EventFilter.h"
#include "Agent.h"
#include "AgentData.h"


EventFilter::EventFilter(const Agent* _agent)
{
    if(!_agent)
    {
        throw "No agent givven";
    }
    
    m_agent = (Agent*)_agent;
    m_events = new SafeQueue<std::tr1::shared_ptr<Event> >(20);
    pthread_create(&m_thread, 0, Trampoline, (void*)this);
}

EventFilter::~EventFilter()
{
    pthread_cancel(m_thread);
    pthread_join(m_thread, 0);
    delete m_events;
}

void* EventFilter::Trampoline(void* _object)
{
    ((EventFilter*)_object)->GrindQueue();
    return 0;
}

void EventFilter::GrindQueue()
{
    while(true)
    {
        std::tr1::shared_ptr<Event> event = m_events->Remove();
        m_agent->GetEvent(event);
    }
}

bool EventFilter::InsertToQueue(const std::tr1::shared_ptr<Event> _event)
{
    if(m_agent->IsRelevant(_event))
    {
        m_events->Insert(_event);
        return true;
    }
    
    return false;
}

