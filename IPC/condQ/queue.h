#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

#include "ADTDefs.h"


typedef struct Queue Queue;

/**
 * a user defined element destroy function 
 */
typedef void (*_elementDestroy)(void* _item);

/*create a cyclonic queue in the size of "_size"*/
Queue*  QueueCreate(size_t _size);
void QueueDestroy(Queue* _queue);

/*push to the head of the queue*/
ADTErr  QueueInsert(Queue* _queue, void* _item);

/*pop from to the tail of the queue to "item"*/
ADTErr  QueueRemove(Queue* _queue, void** _item);

/*check if the queue is empty. return 0 if it's empty*/
int     QueueIsEmpty(Queue* _queue);
void    QueuePrint(Queue* _queue);

#endif /*__QUEUE_H__*/
