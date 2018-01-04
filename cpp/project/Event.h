#ifndef __EVENT_H__
#define __EVENT_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <string>

class Event
{
public:
    Event(const std::string& _topic)
    : m_topic(_topic)
    {}
    
    virtual ~Event(){}
    
    const std::string& GetTopic() const {return m_topic;}

public:
    std::string m_topic;
};

#endif /* __EVENT_H__ */

