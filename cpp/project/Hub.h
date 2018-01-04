#ifndef __HUB_H__
#define __HUB_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <tr1/memory>

#include <pthread.h>
#include <vector>
#include <map>

#include "IHub.h"
#include "Pqueue.h"     // h file in "../cpp_inc"

class Event;
class Agent;
class EventFilter;

class Hub: public IHub
{
public:
    Hub();
    virtual ~Hub();

    bool Subscribe(const Agent* _controller);
    void InsertEvent(const std::tr1::shared_ptr<Event> _event);

private:
    std::vector<std::tr1::shared_ptr<EventFilter> >* m_control;
    SafeQueue<std::tr1::shared_ptr<Event> >* m_events;
    pthread_t m_thread;
    
private:
    Hub(const Hub&);
    Hub& operator=(const Hub&);
    
    static void* FRun(void*);
};

#endif /* __HUB_H__ */

