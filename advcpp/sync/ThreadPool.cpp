#include <iostream>
#include "ThreadPool.h"

namespace advcpp
{

namespace sync
{

ThreadPool::Runner::Runner(ThreadPool& _pool)
: m_pool(_pool)
{}

void ThreadPool::Runner::Run(void)
{
    while(m_pool.m_ShouldPull)
    {
        m_pool.m_spq.TopAndPop().second->Go();
    }
}

ThreadPool::ThreadPool (std::size_t _numOfThreads)
: m_runner(*this)
, m_ShouldAdd(true)
, m_ShouldPull(true)
, m_NoOfThreads(_numOfThreads)
{
    for (std::size_t i = 0; i < _numOfThreads; ++i)
    {
        m_threads.push_back(std::tr1::shared_ptr<Thread<Runner> > (new Thread<Runner> (m_runner, &Runner::Run)));
    }
}

//ThreadPool::~ThreadPool(){}

void ThreadPool::Add(int _priority, std::tr1::shared_ptr<Task> _task)
{
    if(__sync_lock_test_and_set(&m_ShouldAdd, 1))
    {
        m_spq.Push(std::pair<int, std::tr1::shared_ptr<Task> >(_priority, _task));
    }
    else
    {
        throw std::runtime_error(std::strerror(errno));
    }
}

void ThreadPool::Resize(std::size_t _numOfThreads)
{
    if(_numOfThreads == m_NoOfThreads)
    {
        return;
    }
    if(_numOfThreads > m_NoOfThreads)
    {
        for (std::size_t i = m_NoOfThreads; i < _numOfThreads; ++i)
        {
            m_threads.push_back(std::tr1::shared_ptr<Thread<Runner> > (new Thread<Runner> (m_runner, &Runner::Run)));
        }
    }
    
    
    __sync_lock_test_and_set(&m_NoOfThreads, _numOfThreads);
}

class SleepTime: public advcpp::Task
{
public:
    SleepTime(){}

    virtual void Go(){}
};

void ThreadPool::Shutdown()
{
    __sync_lock_test_and_set(&m_ShouldPull, 0);
    __sync_lock_test_and_set(&m_ShouldAdd, 0);
    
    for (std::vector<std::tr1::shared_ptr<Thread<Runner> > >::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        m_spq.Push(std::pair<int, std::tr1::shared_ptr<Task> >(0, std::tr1::shared_ptr<Task>(new SleepTime)));
    }
    
    for (std::vector<std::tr1::shared_ptr<Thread<Runner> > >::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        (*it)->Join();
    }
}

void ThreadPool::FullyGracefulShutdown()
{
    __sync_lock_test_and_set(&m_ShouldAdd, 0);
    
//    for (std::vector<std::tr1::shared_ptr<Thread<Runner> > >::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
//    {
//        m_spq.Push(std::pair<int, std::tr1::shared_ptr<Task> >(0, std::tr1::shared_ptr<Task>(new SleepTime)));
//    }
//    
    for (std::vector<std::tr1::shared_ptr<Thread<Runner> > >::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        m_spq.Push(std::pair<int, std::tr1::shared_ptr<Task> >(0, std::tr1::shared_ptr<Task>(new SleepTime)));
    }
    __sync_lock_test_and_set(&m_ShouldPull, 0);
    
    for (std::vector<std::tr1::shared_ptr<Thread<Runner> > >::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        (*it)->Join();
    }
}

void ThreadPool::BruteShutdown()
{
    __sync_lock_test_and_set(&m_ShouldAdd, 0);
    __sync_lock_test_and_set(&m_ShouldPull, 0);
    
    for (std::vector<std::tr1::shared_ptr<Thread<Runner> > >::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        (*it)->Cancel();
        (*it)->Join();
    }
}


} // namespace sync

} // namespace advcpp
