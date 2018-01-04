#ifndef __EVENT_DATA_H__
#define __EVENT_DATA_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
 
#include <string>
#include "AgentData.h"

class Event
{
public:
    Event(const AgentData* _data);
    Event(const Event& _event);
    virtual ~EventData ();

private:
    std::string m_time;
    std::string m_type;
    std::string m_floor;
    std::string m_room;
    std::string m_payload;   // temporary std::string
    
    Event(){}
};

#endif /* __EVENT_DATA_H__ */

