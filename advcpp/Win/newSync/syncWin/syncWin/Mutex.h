#ifndef __MY_MUTEX_H__
#define __MY_MUTEX_H__


#ifdef __linux__
#include <pthread.h>
#elif _WIN32
#include <windows.h>
#endif

#include "uncopyable.h"

namespace advcpp
{

namespace sync
{

#ifdef __linux__
	typedef pthread_mutex_t Mutex_t;
#elif _WIN32
	typedef CRITICAL_SECTION Mutex_t;
#endif

class Mutex : private uncopyable
{
public:
	friend class NativeMutex;

	explicit Mutex();
	~Mutex();

	void Lock();
	void Unlock();

private:
	Mutex_t m_mutex;
	Mutex_t* GetMutex();
};

class NativeMutex
{
public:
	Mutex_t* GetMutex(Mutex* mu) { return mu->GetMutex(); }
};

} // namespace sync
} // namespace advcpp
#endif /* __MY_MUTEX_H__ */

