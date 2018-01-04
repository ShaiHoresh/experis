#ifndef __IHUB_H__
#define __IHUB_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <tr1/memory>

class Event;
class Agent;

class IHub
{
public:
    virtual ~IHub(){}

    virtual bool Subscribe(const Agent* _controller) = 0;
    virtual void InsertEvent(const std::tr1::shared_ptr<Event> _event) = 0;

};

#endif /* __IHUB_H__ */

