#ifndef __SAFE_PQ_H__
#define __SAFE_PQ_H__

#include "uncopyable.h"
#include <queue>
#include <vector>
#include <cerrno>

#include "Guard.h"
#include "Mutex.h"
#include "CondVar.h"

namespace advcpp
{

namespace sync
{

template <class T>
class SafePQ : private uncopyable
{
public:
	explicit SafePQ();
	~SafePQ();

	void Push(const T&);
	T TopAndPop();

private:
	std::priority_queue<T, std::vector<T> > m_sq;

	mutable Mutex m_mutex;
	CondVar m_cv;
	};

template <class T>
SafePQ<T>::SafePQ()
	: m_cv(&m_mutex)
{}

template <class T>
SafePQ<T>::~SafePQ()
{}

template <class T>
inline void SafePQ<T>::Push(const T& _t)
{
	Guard guard(&m_mutex);

	m_sq.push(_t);
	m_cv.Signal();
}

template <class T>
inline T SafePQ<T>::TopAndPop()
{
	Guard guard(&m_mutex);

	while (m_sq.empty())
	{
		m_cv.Wait();
	}

	T t = m_sq.top();
	m_sq.pop();

	return t;
}

} // namespace sync
} // namespace advcpp

#endif /* __SAFE_PQ_H__ */

