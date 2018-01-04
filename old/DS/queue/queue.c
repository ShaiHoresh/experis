#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Queue
{
    int* m_vec;         /*vec to work on*/
    size_t m_size;        /*size of vector*/
    size_t m_head;        /* index of head in m_vec*/
    size_t m_tail;        /* index of tail in m_vec*/
    size_t m_nItems;      /* number of items in vector*/
};

ADTErr CheckExistence(Queue* _queue);

Queue* QueueCreate(size_t _size)
{
    Queue* queue = NULL;
    
    if(0 == _size)
    {
        return NULL;
    }
    
    queue = malloc(sizeof(Queue));
    
    if(NULL == queue)
    {
        return NULL;
    }
    queue->m_vec = malloc(_size * sizeof(int));
    
    if(NULL == queue->m_vec)
    {
        free(queue);
        return(NULL);
    }
    queue->m_size = _size;
    queue->m_head = 0;
    queue->m_tail = 0;
    queue->m_nItems = 0;
    
    return queue;
}

void QueueDestroy(Queue* _queue)
{
    if(_queue != NULL)
    {
        if(_queue->m_vec != NULL)
        {
            free(_queue->m_vec);
            _queue->m_vec = NULL;
        }
        free(_queue);
    }
    return;
}

ADTErr QueueInsert(Queue* _queue, int _item)
{
    ADTErr errFlag = ERR_OK;
    errFlag = CheckExistence(_queue);
    if(errFlag != ERR_OK)
    {
        return errFlag;
    }
        if(_queue->m_nItems == _queue->m_size)
    {
        return ERR_OVERFLOW;
    }

    _queue->m_vec[_queue->m_head] = _item;
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    _queue->m_nItems ++;

    
    return ERR_OK;
}

ADTErr QueueRemove(Queue* _queue, int* _item)
{
    ADTErr errFlag=  ERR_OK;
    int intFlag = 0;
    if((errFlag = CheckExistence(_queue)) != ERR_OK)
    {
        return errFlag;
    }

    if((intFlag = QueueIsEmpty(_queue)) == 0)
    {
        return ERR_UNDERFLOW;
    }
    
    *_item = _queue->m_vec[_queue->m_tail];
    _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
    _queue->m_nItems --;
    
    return ERR_OK;
}

int QueueIsEmpty(Queue* _queue)
{
    ADTErr errFlag = ERR_OK;
    int intFlag = 0;
    if((errFlag = CheckExistence(_queue)) != ERR_OK)
    {
        return 0;
    }
    intFlag = _queue->m_nItems;
    return intFlag;
}

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
        printf("%d ",_queue->m_vec[(i + _queue->m_tail) % _queue->m_size]);
    }
    return;
}

/*********************************************************************/
/*******************ASSISSTANCE FUNCTION******************************/
/*********************************************************************/
ADTErr CheckExistence(Queue* _queue)
{
    if(NULL == _queue || NULL == _queue->m_vec)
    {
        return ERR_NOT_INITIALIZED;
    }
    return ERR_OK;
}

