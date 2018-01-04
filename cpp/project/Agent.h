#ifndef __Agent_H__
#define __Agent_H__

class AgentData;

#include <iostream>
#include <tr1/memory>
#include "AgentData.h"
#include "Hub.h"
#include "Event.h"

class Agent
{
public:
    Agent(Hub* _hub, const std::tr1::shared_ptr<AgentData> _data)
    :m_hub(_hub), m_data(_data){}
    virtual ~Agent(){}
    
    virtual bool IsRelevant(const std::tr1::shared_ptr<Event> _event)
        {return true;}
    virtual void GetEvent(const std::tr1::shared_ptr<Event> _event)
        {std::cout << "got event: " << _event->m_topic << std::endl;}
    
protected:
    Hub* m_hub;

private:
    std::tr1::shared_ptr<AgentData> m_data;
};

#endif /* __Agent_H__ */

