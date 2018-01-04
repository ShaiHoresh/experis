#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <vector>                       // threads container
#include <boost/core/noncopyable.hpp>   // noncopyable
#include <tr1/memory>                   // shared_ptr

#include "Thread.h"
#include "SafePQ.h"
#include "Task.h"

namespace advcpp
{

namespace sync
{

class ThreadPool: private boost::noncopyable
{
public:
    explicit ThreadPool (std::size_t);
/*    ~ThreadPool ();     // default dtor*/

    void Add(int _priority, std::tr1::shared_ptr<Task> _task);
    void Shutdown();
    void BruteShutdown();
    void FullyGracefulShutdown();
    
    void Resize(std::size_t);
    
private:
    struct Runner
    {
        Runner(ThreadPool&);
        void Run(void);
        
        ThreadPool& m_pool;
    };


private:
    Runner m_runner;
    bool m_ShouldAdd;
    bool m_ShouldPull;
    std::size_t m_NoOfThreads;
    std::vector<std::tr1::shared_ptr<Thread<Runner> > > m_threads;
    SafePQ<std::pair<int, std::tr1::shared_ptr<Task> > > m_spq;
};

} // namespace sync

} // namespace advcpp

#endif /* __THREAD_POOL_H__ */



