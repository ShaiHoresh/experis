#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>


namespace advcpp
{

class Task
{
public:
    virtual ~Task(){}
    virtual void Go() = 0;
};

} // namespace nm
#endif /* __TASK_H__ */

