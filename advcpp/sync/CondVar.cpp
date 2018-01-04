#include <stdexcept>
#include <cstring>
#include <cerrno>

#include "CondVar.h"
#include "Mutex.h"


namespace advcpp
{

namespace sync
{

CondVar::CondVar (Mutex* _mutex)
{
    m_mutex = NativeMutex().GetMutex(_mutex);
    
    if(pthread_cond_init(&m_cond, 0))
    {
        throw std::runtime_error(std::strerror(errno));
    }
}


CondVar::~CondVar ()
{
    pthread_cond_destroy(&m_cond);
}

void CondVar::Wait() 
{
//    Guard guard(m_mutex);
//    while()
//    {
        if(pthread_cond_wait(&m_cond, m_mutex))
        {
            throw std::runtime_error(std::strerror(errno));
        }
//    }
}

void CondVar::Broadcast()
{
    if(pthread_cond_broadcast(&m_cond))
    {
        throw std::runtime_error(std::strerror(errno));
    }
}

void CondVar::Signal()
{
    if(pthread_cond_signal(&m_cond))
    {
        throw std::runtime_error(std::strerror(errno));
    }
}
       
    
} // namespace sync

} // namespace advcpp

