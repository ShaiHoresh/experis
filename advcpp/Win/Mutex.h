#ifndef __MY_MUTEX_H__
#define __MY_MUTEX_H__

#include <boost/core/noncopyable.hpp>
#include <pthread.h>
namespace advcpp
{
 
namespace sync
{

class Mutex: private boost::noncopyable
{
public:
    explicit Mutex();
    ~Mutex();

    void Lock();
    void Unlock();
    
    
    friend class NativeMutex;
    
private:
    pthread_mutex_t m_mutex;
    pthread_mutex_t* GetMutex();
};

class NativeMutex 
{
public:
    pthread_mutex_t* GetMutex(Mutex* mu) {return mu->GetMutex();}    // a problematic one...
};

} // namespace sync
} // namespace advcpp
#endif /* __MY_MUTEX_H__ */

