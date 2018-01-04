#ifndef __CONDVAR_H__
#define __CONDVAR_H__

#include <boost/core/noncopyable.hpp>
#include <pthread.h>
#include "Mutex.h"

namespace advcpp
{

namespace sync
{
    

class CondVar: private boost::noncopyable
{
public:
    CondVar (Mutex* _mutex);
    ~CondVar ();

    void Wait();
    void Broadcast();
    void Signal();
    
private:
    pthread_cond_t m_cond;
    pthread_mutex_t* m_mutex;
};    
    
    
} // namespace sync

} // namespace advcpp

#endif /* __CONDVAR_H__ */
