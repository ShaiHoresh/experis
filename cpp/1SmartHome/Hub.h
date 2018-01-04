#ifndef __HUB_H__
#define __HUB_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <pthread.h>


class Hub
{
public:
    Hub();
    virtual ~Hub ();
    
    virtual void InsertToHubsQ(const Event& _event);
    
    virtual void PublishEvent();
    
    virtual bool Subscribe(Agent* _agent);

private:
    Pqueue<Event*> m_EventQ;

    std::multimap<Agent*, std::string> m_map;   // std::string == topic. TODO change to event-filter

    static void* Publish(Hub* _hub);
    virtual void Notify(const Event& _event);
};

#endif /* __HUB_H__ */

