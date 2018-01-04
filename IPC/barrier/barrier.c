#include <pthread.h>    /* mutex, cond, etc. */
#include <stdlib.h>     /* malloc */
#include <unistd.h>     /* temporary sleep */
#include <stdio.h>
#include "barrier.h"

#define FAIL 1
#define SUCCESS 0

struct Barrier
{
    unsigned int        m_capacity;
    unsigned int        m_counter;
    int                 m_destroyFlag;
    pthread_cond_t      m_cond;
    pthread_mutex_t     m_mutex;
};

Barrier* BarrierCreate(unsigned int _capacity)
{
    /* declaration and int of cond & mutex */
    Barrier* barrier;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    /* check validity of capacity */
    if(!_capacity)
    {
        return NULL;
    }
        
    /* malloc struct */
    barrier = malloc(sizeof(Barrier));
    if(!barrier)
    {
        return NULL;
    }    
    
    /* init struct fields */
    barrier->m_capacity = _capacity;
    barrier->m_counter = 0;
    barrier->m_destroyFlag = 0;
    barrier->m_cond = cond;
    barrier->m_mutex = mutex;
    
    return barrier;
}

void BarrierDestroy(Barrier* _barrier)
{
    /* check */
    if(!_barrier)
    {
        return;
    }
    
    _barrier->m_destroyFlag = 1;
    
    /* TODO wait for all other thread */
    sleep(5);
    
    /* destroy pthread "products" */
    pthread_mutex_destroy(&_barrier->m_mutex);
    pthread_cond_destroy(&_barrier->m_cond);
        
    /* free struct */
    free(_barrier);
}

int BarrierWait(Barrier* _barrier)
{
    /* check */
    if(!_barrier)
    {
        return -1;
    }
    
    /* increment counter under lock */
    pthread_mutex_lock(&(_barrier->m_mutex)); /* TODO check error */
    _barrier->m_counter++;
    
    
    /* TODO change if to while */
    if(_barrier->m_counter != _barrier->m_capacity)/*|| _barrier->m_destroyFlag == 1)*/
    {
        pthread_cond_wait(&(_barrier->m_cond), &_barrier->m_mutex);
        /* TODO take care of destroy flag */
    }
    else
    {
        pthread_cond_broadcast(&_barrier->m_cond);
        _barrier->m_counter = 0;
    }
    
    pthread_mutex_unlock(&(_barrier->m_mutex));
    
    return 1;
}


