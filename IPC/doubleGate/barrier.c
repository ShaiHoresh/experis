#include <pthread.h>    /* mutex, cond, etc. */
#include <stdlib.h>     /* malloc */
#include <unistd.h>     /* temporary sleep */
#include <stdio.h>
#include "barrier.h"

#define FAIL 1
#define SUCCESS 0

#define OPEN_GATE 1
#define CLOSE_GATE 0


struct Barrier
{
    unsigned int        m_capacity;
    unsigned int        m_entering;
    int                 m_destroyFlag;
    pthread_cond_t      m_batchCond;
    pthread_cond_t      m_countCond;
    pthread_cond_t      m_exitCond;
    pthread_mutex_t     m_mutex;
    unsigned int        m_curBatch;
    unsigned int        m_counter;
    unsigned int        m_running;
    unsigned int        m_out;
    unsigned int        m_exiting;
};

Barrier* BarrierCreate(unsigned int _capacity)
{
    /* declaration and int of cond & mutex */
    Barrier* barrier;
/*    pthread_cond_t batchCond;
    pthread_cond_t m_countCond;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;*/
    
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
    
    pthread_cond_init(&barrier->m_batchCond, NULL);
    pthread_cond_init(&barrier->m_countCond, NULL);
    pthread_cond_init(&barrier->m_exitCond, NULL);
    pthread_mutex_init(&barrier->m_mutex, NULL);
    
    /* init struct fields */
    barrier->m_capacity = _capacity;
    barrier->m_entering = 0;
    barrier->m_destroyFlag = 0;
    /*&barrier->m_batchCond = &enterCond;
    &barrier->m_countCond = &exitCond;
    &barrier->m_mutex = &mutex;*/
    barrier->m_curBatch = 0;
    barrier->m_running = 0;
    barrier->m_out = 0;
    barrier->m_exiting = 0;
    barrier->m_counter = 0;
    
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
    pthread_cond_destroy(&_barrier->m_countCond);
    pthread_cond_destroy(&_barrier->m_batchCond);
        
    /* free struct */
    free(_barrier);
}

int BarrierWait(Barrier* _barrier, CallBack _cb, void* _context)
{
    /* declarations*/
    unsigned int myBatch, ID;

    /* check */
    if(!_barrier)
    {
        return -1;
    }
  
    pthread_mutex_lock(&_barrier->m_mutex);      /* error handling */
    
    ID = _barrier->m_counter++;
    
    myBatch = ID / _barrier->m_capacity;
    printf("ID = %d, myBatch = %d, curBatch = %d\n", ID, myBatch, _barrier->m_curBatch);

    while(myBatch != _barrier->m_curBatch)
    {
        pthread_cond_wait(&_barrier->m_batchCond, &_barrier->m_mutex);
    }
    
    _barrier->m_entering++;

    printf("after first gate\n");
    _barrier->m_exiting = 0;
    _barrier->m_out = 0;
    
    while(_barrier->m_entering < _barrier->m_capacity)
    {
        pthread_cond_wait(&_barrier->m_countCond, &_barrier->m_mutex);
    }
    printf("after second gate\n");

    if(_barrier->m_entering == _barrier->m_capacity) // w/o if
    {
    }
        pthread_cond_broadcast(&_barrier->m_countCond);
    pthread_mutex_unlock(&_barrier->m_mutex);
    
    if(_cb)
    {
        _cb(_context);
    }
    
    pthread_mutex_lock(&_barrier->m_mutex);
    _barrier->m_exiting++;
    
    printf("_barrier->m_exiting = %d, _barrier->m_entering = %d\n", _barrier->m_exiting, _barrier->m_entering);
    
    while(_barrier->m_exiting < _barrier->m_capacity)
    {
        pthread_cond_wait(&_barrier->m_exitCond, &_barrier->m_mutex);
    }

    _barrier->m_out++;
    
    if(_barrier->m_entering != 0)
    {
        _barrier->m_entering = 0;
        pthread_cond_broadcast(&_barrier->m_exitCond);
        printf("\t\tFirst from third gate\n");
    }
    
    if(_barrier->m_out == _barrier->m_capacity)
    {
        _barrier->m_curBatch++;
        pthread_cond_broadcast(&_barrier->m_batchCond);
        printf("\t\tlast from third gate\n");
    }
    
    pthread_mutex_unlock(&_barrier->m_mutex);
    
    /*  REAL CODE   */
    return 1;
}

















