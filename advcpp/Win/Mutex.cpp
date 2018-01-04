#include "Mutex.h"
#include <stdexcept>
#include <cstring>
#include <cerrno>

namespace advcpp
{
namespace sync
{

Mutex::Mutex()
{
    if(pthread_mutex_init(&m_mutex, 0))
    {
        throw std::runtime_error(std::strerror(errno));
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock()
{
    if(pthread_mutex_lock(&m_mutex))
    {
        throw std::runtime_error(std::strerror(errno));
    }
}

void Mutex::Unlock()
{
    if(pthread_mutex_unlock(&m_mutex))
    {
        throw std::runtime_error(std::strerror(errno));
    }
}

pthread_mutex_t* Mutex::GetMutex()
{
    return &m_mutex;
}

} //namespace advcpp

} //namespace sync
