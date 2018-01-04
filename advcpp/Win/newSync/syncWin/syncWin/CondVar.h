#ifndef __CONDVAR_H__
#define __CONDVAR_H__

#ifdef __linux__
#include <pthread.h>
#elif _WIN32
#include <Windows.h>
#endif

#include "uncopyable.h"
#include "Mutex.h"

namespace advcpp
{

namespace sync
{

#ifdef __linux__
	typedef pthread_mutex_t Mutex_t;
	typedef pthread_cond_t Cond_t;
#elif _WIN32
	typedef CRITICAL_SECTION Mutex_t;
	typedef CONDITION_VARIABLE Cond_t;
#endif

class CondVar : private uncopyable
{
public:
	CondVar(Mutex* _mutex);
	~CondVar();

	void Wait();
	void Broadcast();
	void Signal();

private:
	Mutex_t* m_mutex;
	Cond_t m_cond;
};


} // namespace sync

} // namespace advcpp

#endif /* __CONDVAR_H__ */
