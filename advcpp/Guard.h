#ifndef __GUARD_H__
#define __GUARD_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
namespace advcpp
{

#include <pthread.h>


class Guard
{
public:
    Guard(pthread_mutex_t* _mutex)
    {
        if(_mutex)
        {
            m_mutex = _mutex;
            pthread_mutex_lock(m_mutex);
        }
    }
    ~Guard()
    {
        pthread_mutex_unlock(m_mutex);
    }

private:
    void operator=(const Guard&);
    Guard(const Guard&);
    
    pthread_mutex_t* m_mutex;
};

} // namespace advcpp
#endif /* __GUARD_H__ */

