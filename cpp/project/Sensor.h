#ifndef __SENSOR_H__
#define __SENSOR_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <pthread.h>
#include "Agent.h"

class Hub;
class Event;

class Sensor: public Agent
{
public:
    Sensor(Hub* _hub, const std::tr1::shared_ptr<AgentData> _data);
    virtual ~Sensor();
    
    void Publish(std::tr1::shared_ptr<Event> _event);
    virtual void CreateEvent() = 0;
    virtual bool IsRelevant(const std::tr1::shared_ptr<Event>& _event) = 0;
        
    virtual void GetEvent(const std::tr1::shared_ptr<Event>& _event) = 0;

protected:
    pthread_t m_thread;
};

#endif /* __SENSOR_H__ */

