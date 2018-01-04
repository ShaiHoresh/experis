#include <stdexcept>
#include <cstring>
#include <cerrno>

#include "CondVar.h"
#include "Mutex.h"
namespace advcpp
{

namespace sync
{

CondVar::CondVar(Mutex* _mutex)
{
	m_mutex = NativeMutex().GetMutex(_mutex);
#ifdef __linux__
	if (pthread_cond_init(&m_cond, 0))
	{
		throw std::runtime_error(std::strerror(errno));
	}
#elif _WIN32
	InitializeConditionVariable(&m_cond);
#endif
}


CondVar::~CondVar()
{
#ifdef __linux__
	pthread_cond_destroy(&m_cond);
#endif
}

void CondVar::Wait()
{
#ifdef __linux__
	if (pthread_cond_wait(&m_cond, m_mutex))
	{
		throw std::runtime_error(std::strerror(errno));
	}
#elif _WIN32
	SleepConditionVariableCS(&m_cond, m_mutex, INFINITE);
#endif
}

void CondVar::Broadcast()
{
#ifdef __linux__
	if (pthread_cond_broadcast(&m_cond))
	{
		throw std::runtime_error(std::strerror(errno));
	}
#elif _WIN32
	WakeAllConditionVariable(&m_cond);
#endif
}

void CondVar::Signal()
{
#ifdef __linux__
	if (pthread_cond_signal(&m_cond))
	{
		throw std::runtime_error(std::strerror(errno));
	}
#elif _WIN32
	WakeConditionVariable(&m_cond);
#endif
}


} // namespace sync

} // namespace advcpp

