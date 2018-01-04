#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__

/** 
 * @brief wrapper to the stl queue, using semaphores and mutex.
 *  has only CTOR, DTOR, Insert (push) & Remove (front and pop).
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
#include <queue>
#include <semaphore.h>

#include <pthread.h>

const unsigned int DEFAULT_SIZE = 100;

template <class T>
class SafeQueue
{
public:
    explicit SafeQueue(unsigned int _size = DEFAULT_SIZE);
    virtual ~SafeQueue();
   
    void Insert(const T& _data);
    T Remove();
        
private:
    std::queue<T> m_q;
    sem_t m_empty;
    sem_t m_full;
    pthread_mutex_t m_mutex;
    
    
    SafeQueue(const SafeQueue&);
    SafeQueue& operator=(const SafeQueue&);
};

template <class T>
SafeQueue<T>::SafeQueue(unsigned int _size)
{
    if(pthread_mutex_init(&m_mutex, 0))
    {
        throw("mutex failure");
    }
    if(sem_init(&m_empty, 0, _size))
    {
        pthread_mutex_destroy(&m_mutex);
        throw("sem failure");
    }
    if(sem_init(&m_full, 0, 0))
    {
        pthread_mutex_destroy(&m_mutex);
        sem_destroy(&m_empty);
        throw("sem failure");
    }
}

template <class T>
SafeQueue<T>::~SafeQueue()
{
    pthread_mutex_destroy(&m_mutex);
    sem_destroy(&m_empty);
    sem_destroy(&m_full);
}

template <class T>
void SafeQueue<T>::Insert(const T& _data)
{
    if(sem_wait(&m_empty))
    {
        //
    }
    
    if(pthread_mutex_lock(&m_mutex))
    {
        //
    }
    
    m_q.push(_data);
    
    if(pthread_mutex_unlock(&m_mutex))
    {
        //
    }
    
    if(sem_post(&m_full))
    {
        //
    }

}

template <class T>
T SafeQueue<T>::Remove()
    {
        if(sem_wait(&m_full))
        {
            //
        }
        
        if(pthread_mutex_lock(&m_mutex))
        {
            //
        }
        
        T data = m_q.front();
        m_q.pop();
        
        if(pthread_mutex_unlock(&m_mutex))
        {
            //
        }
        
        if(sem_post(&m_empty))
        {
            //
        }
        
        return data; 
    }

#endif /* __SAFE_QUEUE_H__ */


