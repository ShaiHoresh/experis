#ifndef __AGENT_H__
#define __AGENT_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
#include <pthread.h>
#include "Pqueue.h"

class AgentData;
class Event;
class Hub;

class Agent
{
public:
    Agent(const AgentData* _data, Hub* _hub);
    virtual ~Agent();

    virtual void Subscribe();
    virtual void Publish();
    virtual void Update();
    

protected:
    AgentData* m_data;
    Pqueue<Event*> m_q;
    Hub* m_hub;
    pthread_t m_thread;
    
private:
    Agent(const Agent&);
    Agent& operator=(const Agent&);
};

#endif /* __AGENT_H__ */

