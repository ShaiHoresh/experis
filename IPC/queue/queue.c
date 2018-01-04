#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "queue.h"

#define MAGIC 0xFABCABAF

struct Queue
{
    unsigned int        m_magic;
    void*               *m_array;       /*vec to work on*/
    size_t              m_size;         /*size of vector*/
    size_t              m_head;         /* index of head in m_array*/
    size_t              m_tail;         /* index of tail in m_array*/
    sem_t               m_empty;        /* count down semaphore */
    sem_t               m_full;         /* count up semaphore */
    pthread_mutex_t     m_mutex;        /* guard */
};

ADTErr CheckExistence(Queue* _queue);

Queue* QueueCreate(size_t _size)
{
    Queue* queue = NULL;
    sem_t empty, full;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    if(0 == _size)
    {
        return NULL;
    }
    
    queue = malloc(sizeof(Queue));
    
    if(NULL == queue)
    {
        return NULL;
    }
    queue->m_array = malloc(_size * sizeof(void*));
    
    if(NULL == queue->m_array)
    {
        free(queue);
        return NULL;
    }
    
    sem_init(&empty, 0, _size);     /* TODO check errors */
    sem_init(&full, 0, 0);
    
    if(SEM_FAILED == &empty || SEM_FAILED == &full)
    {
        QueueDestroy(queue, NULL);
        return NULL;
    }
    
    queue->m_size = _size;
    queue->m_head = 0;
    queue->m_tail = 0;
    queue->m_empty = empty;
    queue->m_full = full;
    queue->m_mutex = mutex;
    
    return queue;
}

void QueueDestroy(Queue* _queue, _elementDestroy _action) /* add destoyer for each element, sem and mutex */
{
    int i;
    
    if(_queue != NULL)
    {
        if(_queue->m_array != NULL)
        {
            if(NULL != _action)
            {
                for(i = 0; i < _queue->m_size; ++i)
                {
                    _action(_queue->m_array[i]);
                }
            }
            free(_queue->m_array);
            _queue->m_array = NULL;
        }
        
       /* pthread_mutex_destroy(_queue->m_mutex);
        sem_destroy(_queue->m_full);
        sem_destroy(_queue->m_empty);*/
        
        free(_queue);
    }
    return;
}

ADTErr QueueInsert(Queue* _queue, void* _item)
{
    ADTErr errFlag = ERR_OK;
    
    
    errFlag = CheckExistence(_queue);
    if(errFlag != ERR_OK)
    {
        return errFlag;
    }

    sem_wait(&(_queue->m_empty));
    pthread_mutex_lock(&(_queue->m_mutex));
    
    _queue->m_array[_queue->m_head] = _item;
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    
    pthread_mutex_unlock(&(_queue->m_mutex));
    sem_post(&(_queue->m_full));
    
    return ERR_OK;
}

ADTErr QueueRemove(Queue* _queue, void** _item)
{
    ADTErr errFlag=  ERR_OK;

     
    if((errFlag = CheckExistence(_queue)) != ERR_OK)
    {
        return errFlag;
    }

    sem_wait(&(_queue->m_full));
    pthread_mutex_lock(&(_queue->m_mutex));
    
    *_item = _queue->m_array[_queue->m_tail];
    _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;

    pthread_mutex_unlock(&(_queue->m_mutex));
    sem_post(&(_queue->m_empty));

    
    return ERR_OK;
}

int QueueIsEmpty(Queue* _queue)
{
    ADTErr errFlag = ERR_OK;
    int nItems;
    if((errFlag = CheckExistence(_queue)) != ERR_OK)
    {
        return 0;
    }
    
    sem_getvalue(&(_queue->m_full), &nItems);
    
    return nItems;
}
/*
void QueuePrint(Queue* _queue)
{
    ADTErr errFlag = ERR_OK;
    int i = 0;
    if((errFlag = CheckExistence(_queue)) != ERR_OK)
    {
        return;
    }
    for(i = 0; i < _queue->m_nItems; ++i)
    {
        printf("%d ",_queue->m_array[(i + _queue->m_tail) % _queue->m_size]);
    }
    return;
}*/

/*********************************************************************/
/*******************ASSISSTANCE FUNCTION******************************/
/*********************************************************************/
ADTErr CheckExistence(Queue* _queue)
{
    if(NULL == _queue || NULL == _queue->m_array)
    {
        return ERR_NOT_INITIALIZED;
    }
    return ERR_OK;
}

