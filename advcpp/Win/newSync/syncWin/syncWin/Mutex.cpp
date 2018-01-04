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
#ifdef __linux__
	if (pthread_mutex_init(&m_mutex, 0))
	{
		throw std::runtime_error(std::strerror(errno));
	}
#elif _WIN32
	InitializeCriticalSection(&m_mutex);
#endif
}

Mutex::~Mutex()
{
#ifdef __linux__
	pthread_mutex_destroy(&m_mutex);
#elif _WIN32
	DeleteCriticalSection(&m_mutex);
#endif
}

void Mutex::Lock()
{
#ifdef __linux__
	if (pthread_mutex_lock(&m_mutex))
	{
		throw std::runtime_error(std::strerror(errno));
	}
#elif _WIN32
	EnterCriticalSection(&m_mutex);
#endif
}

void Mutex::Unlock()
{
#ifdef __linux__
	if (pthread_mutex_unlock(&m_mutex))
	{
		throw std::runtime_error(std::strerror(errno));
	}
#elif _WIN32
	LeaveCriticalSection(&m_mutex);
#endif
}

Mutex_t* Mutex::GetMutex()
{
	return &m_mutex;
}

} //namespace advcpp

} //namespace sync
