#ifndef __THREAD_H__
#define __THREAD_H__



#ifdef __linux__
#include <pthread.h>
#elif _WIN32
#include <Windows.h>
#endif

#include <stdexcept>
#include <cstring>
#include <cerrno>

#include "uncopyable.h"

#ifdef __linux__
	typedef void* RetVal;
	typedef pthread_t Thread_t;
#elif _WIN32
	typedef DWORD WINAPI RetVal;
	typedef HANDLE Thread_t;
#endif

namespace advcpp
{

namespace sync
{

template <class T>
class Thread : private uncopyable
{
public:
	explicit Thread(T&, void(T::*RunFunc)(void));
	~Thread();

	void Join();
	void Detach();
	void Cancel();

	std::size_t GetId() const;

private:
	Thread_t m_thread;
	T& m_object;
	void (T::*m_runFunc)(void);
	bool m_isJoinedOrDetached;

	static RetVal Run(void*);
};

template <class T>
Thread<T>::Thread(T& _obj, void (T::*_func)(void))
	: m_object(_obj)
	, m_runFunc(_func)
	, m_isJoinedOrDetached(false)
{
#ifdef __linux__
if (pthread_create(&m_thread, 0, Run, this))
{
	throw std::runtime_error(std::strerror(errno));
}
#elif _WIN32
	m_thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Run, this, 0, 0);
#endif
}

template <class T>
Thread<T>::~Thread()
{
	if (!m_isJoinedOrDetached)
	{
#ifdef __linux__
	pthread_cancel(m_thread);
#elif _WIN32
	TerminateThread(m_thread, 0);
#endif
	}
}

template <class T>
void Thread<T>::Join()
{
#ifdef __linux_
if (pthread_join(m_thread, 0))
{
	throw std::runtime_error(std::strerror(errno));
}
#elif _WIN32
	WaitForSingleObject(m_thread, INFINITE);
#endif
	m_isJoinedOrDetached = true;
}

template <class T>
void Thread<T>::Detach()
{
#ifdef __linux_
if (pthread_detach(m_thread))
{
	throw std::runtime_error(std::strerror(errno));
}
#elif _WIN32
	CloseHandle(m_thread);
#endif
	m_isJoinedOrDetached = true;
}

template <class T>
void Thread<T>::Cancel()
{
#ifdef __linux__
	pthread_cancel(m_thread);
#elif _WIN32
	TerminateThread(m_thread, 0);
#endif
	m_isJoinedOrDetached = true;
}

template <class T>
RetVal Thread<T>::Run(void* _this)
{
	T* object = &(static_cast<Thread<T>*>(_this)->m_object);
	void (T::*RunTask)(void) = (static_cast<Thread<T>*>(_this)->m_runFunc);
	(object->*RunTask)();

	return static_cast<RetVal>(_this);
}

template <class T>
std::size_t Thread<T>::GetId() const
{
#ifdef __linux__
	return static_cast<std::size_t>(pthread_self());
#elif _WIN32
	return static_cast<std::size_t>(GetCurrentThreadId());
#endif
}


} // namespace sync

} // namespace advcpp

#endif /* __THREAD_H__ */

