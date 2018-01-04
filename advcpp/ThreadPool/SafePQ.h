#ifndef __SAFE_PQ_H__
#define __SAFE_PQ_H__

#include <boost/core/noncopyable.hpp>
#include <queue>
#include <vector>
#include <cerrno>
#include <stdexcept>
#include <cstring>


#include "Mutex.h"
#include "CondVar.h"



namespace advcpp
{

namespace sync
{

template <class T, class U> // T - object's class, U - comperator
class SafePQ: private boost::noncopyable
{
public: 
    explicit SafePQ ();
    ~SafePQ ();
    
    bool Empty() const;
    std::size_t Size() const;
    void Pop();
    T& Top() const;
    void Push(const T&);

private:
    std::priority_queue<T, std::vector<T>, U> m_sq;
    
    Mutex m_mutex;
    CondVar m_cv;
};

template <class T, class U>
SafePQ<T, U>::SafePQ()
: m_cv(&m_mutex)
{}

template <class T, class U>
SafePQ<T, U>::~SafePQ()
{
/*    delete m_sq;*/
}
    
} // namespace sync

} // namespace advcpp

#endif /* __SAFE_PQ_H__ */

