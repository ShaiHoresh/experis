#ifndef __SmokeDet_H__
#define __SmokeDet_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <tr1/memory>
#include "ICreator.h"
#include "Sensor.h"


class SmokeDet: public Sensor
{
public:
    SmokeDet(std::tr1::shared_ptr<AgentData> _data, Hub* _hub);
    ~SmokeDet();
    
    void CreateEvent();
    static void* PublishEv(void*);
    
    virtual bool IsRelevant(const std::tr1::shared_ptr<Event>& _event);
        
    virtual void GetEvent(const std::tr1::shared_ptr<Event>& _event);
};

#endif /* __SmokeDet_H__ */

