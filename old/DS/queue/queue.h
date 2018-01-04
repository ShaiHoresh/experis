#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "ADTDefs.h"

typedef struct Queue Queue;

/*create a cyclonic queue in the size of "_size"*/
Queue*  QueueCreate(size_t _size);
void    QueueDestroy(Queue* _queue);

/*push to the head of the queue*/
ADTErr  QueueInsert(Queue* _queue, int _item);

/*pop from to the tail of the queue to "item"*/
ADTErr  QueueRemove(Queue* _queue, int* _item);

/*check if the queue is empty. return 0 if it's empty*/
int     QueueIsEmpty(Queue* _queue);
void    QueuePrint(Queue* _queue);

#endif /*__QUEUE_H_*/
