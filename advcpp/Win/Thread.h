#ifndef __THREAD_H__
#define __THREAD_H__

#include <boost/core/noncopyable.hpp>
#include <stdexcept>
#include <pthread.h>
#include <cstring>
#include <cerrno>

namespace advcpp
{

namespace sync
{

template <class T>
class Thread: private boost::noncopyable
{
public:
    explicit Thread(T&, void (T::*RunFunc)(void));
    ~Thread();

    void Join();
    void Detach();
    void Cancel();
    
    std::size_t GetId() const;
    
private:
    pthread_t m_thread;
    T& m_object;
    void (T::*m_runFunc)(void);
    bool m_isJoinedOrDetached;
    
    static void* Run(void*);
};

template <class T>
Thread<T>::Thread(T& _obj, void (T::*_func)(void))
: m_object(_obj)
, m_runFunc(_func)
, m_isJoinedOrDetached(false)
{
    if(pthread_create(&m_thread, 0, Run, this))
    {
        throw std::runtime_error(std::strerror(errno));
    }
}

template <class T>
Thread<T>::~Thread()
{
    if(!m_isJoinedOrDetached)
    {
        pthread_cancel(m_thread);
    }
}

template <class T>
void Thread<T>::Join()
{
    if(pthread_join(m_thread, 0))
    {
        throw std::runtime_error(std::strerror(errno));
    }
    m_isJoinedOrDetached = true;
}

template <class T>
void Thread<T>::Detach()
{
    if(pthread_detach(m_thread))
    {
        throw std::runtime_error(std::strerror(errno));
    }
    m_isJoinedOrDetached = true;
}

template <class T>
void Thread<T>::Cancel()
{
    pthread_cancel(m_thread);
    m_isJoinedOrDetached = true;
}

template <class T>
void* Thread<T>::Run(void* _this)
{
    T* object = &(static_cast<Thread<T>*>(_this)->m_object);
    void (T::*RunTask)(void) = (static_cast<Thread<T>*>(_this)->m_runFunc);
    (object->*RunTask)();
    
    return static_cast<void*>(_this);
}

template <class T>
std::size_t Thread<T>::GetId() const
{
    return static_cast<std::size_t>(pthread_self());
}


} // namespace sync

} // namespace advcpp

#endif /* __THREAD_H__ */

