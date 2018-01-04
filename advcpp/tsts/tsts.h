#ifndef __THREADSAFE_TEMPLATE_SINGLETON_H__
#define __THREADSAFE_TEMPLATE_SINGLETON_H__

#include <tr1/memory>
#include "Guard.h"

namespace advcpp
{

template <class T>
class Singleton
{
public:
    ~Singleton();
    static std::tr1::shared_ptr<T> GetInstance();

private:
    static std::tr1::shared_ptr<T> m_instance;
    static pthread_mutex_t m_mutex;
    static char m_exist;
    
private:
    Singleton();
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
};

template <class T>
std::tr1::shared_ptr<T> Singleton<T>::m_instance;

template <class T>
pthread_mutex_t Singleton<T>::m_mutex = PTHREAD_MUTEX_INITIALIZER;

template <class T>
char Singleton<T>::m_exist = 0;

template <class T>
inline std::tr1::shared_ptr<T> Singleton<T>::GetInstance()
{
    if(!__sync_fetch_and_or(&m_exist, 0))
    {
        Guard guard(&m_mutex);
        if(!__sync_fetch_and_or(&m_exist, 0))
        {
            m_instance = std::tr1::shared_ptr<T> (new T);
            __sync_fetch_and_add(&m_exist, 1);
        }
    }
    
    return m_instance;
}

} //    namespace advcpp
#endif /* __THREADSAFE_TEMPLATE_SINGLTON_H__ */

