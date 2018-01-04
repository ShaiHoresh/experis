#ifndef __NAME_H__
#define __NAME_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "Agent.h"

class Sprinkler: public Agent
{
public:
    Sprinkler(std::tr1::shared_ptr<AgentData>, Hub*);
    ~Sprinkler();
    
    virtual bool IsRelevant(const std::tr1::shared_ptr<Event> _event);
    virtual void GetEvent(const std::tr1::shared_ptr<Event> _event);
};


#endif /* __NAME_H__ */

