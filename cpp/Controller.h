#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
 
class Hub;
class Event;

class Controller
{
public:
    Controller(Hub* _hub);
    virtual ~Controller();
    
    void OnEvent(Event* _event);

private:
    /* data */
};

#endif /* __CONTROLLER_H__ */

