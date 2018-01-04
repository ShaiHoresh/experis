#include <iostream>

#include "Hub.h"
#include "EventFilter.h"
#include "Event.h"
#include "Agent.h"

Hub::Hub()
{
    m_events = new SafeQueue<std::tr1::shared_ptr<Event> >(10);
    m_control = new std::vector<std::tr1::shared_ptr<EventFilter> >;
    pthread_create(&m_thread, 0, FRun, (void*)this);
}

Hub::~Hub()
{
    pthread_cancel(m_thread);
    pthread_join(m_thread, 0);
    delete m_events;
    delete m_control;
}

bool Hub::Subscribe(const Agent* _controller)
{
    if(_controller) // TODO check if the agent exists already in the vector
    {
        std::tr1::shared_ptr<EventFilter> filter(new EventFilter(_controller)); // create EventFilter
        m_control->push_back(filter);// push to vector
        return true;
    }
    
    return false;
}

void Hub::InsertEvent(const std::tr1::shared_ptr<Event> _event)
{
    std::cout << "Hub InsertEvent: " << _event->GetTopic() << std::endl;
    m_events->Insert(_event);
}

void* Hub::FRun(void* _object)
{
    while(true)
    {
        std::tr1::shared_ptr<Event> event = ((Hub*)_object)->m_events->Remove();
        for (std::vector<std::tr1::shared_ptr<EventFilter> >::iterator it = ((Hub*)_object)->m_control->begin() ; it != ((Hub*)_object)->m_control->end(); ++it)
        {
            (*it)->InsertToQueue(event);
        }
    }
}






