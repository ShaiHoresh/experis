#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define QUEUE_SIZE 10

void PrintFormat(size_t _flag);

void TestCreateNormal();
void TestCreateWInitSizeZero();

void TestAddNormal();
void TestAddVectorNull();
void TestAddMoreThanSize();

void TestDeleteNormal();
void TestDeleteTooMuch();

void TestDeleteIfQueueIsEmpty();
void TestDeleteQueueNull();
void TestDeleteAndAddInLoop();


int main()
{
    TestCreateNormal();
    TestCreateWInitSizeZero();

    TestAddNormal();
    TestAddVectorNull();
    TestAddMoreThanSize();
    
    TestDeleteNormal();
    TestDeleteTooMuch();
    TestDeleteIfQueueIsEmpty();
    TestDeleteQueueNull();
    
    TestDeleteAndAddInLoop();
    
    return 0;
}

void TestCreateNormal()
{
    Queue* queue;
    int flag = 0;
    
    queue = QueueCreate(QUEUE_SIZE);
	if(NULL == queue)
	{
	    flag = 1;
	}
	PrintFormat(flag);
    printf("Test create normal\n");

	QueueDestroy(queue);
	return;
}

void TestCreateWInitSizeZero()
{
    Queue* queue;
    int flag = 1;
    
    queue = QueueCreate(0);
	if(NULL == queue)
	{
	    flag = 0;
	}
	PrintFormat(flag);
    printf("Test create initial size 0\n");

	QueueDestroy(queue);
	return;
}

void TestAddNormal()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue;
    int i;
    queue = QueueCreate(QUEUE_SIZE);
    for(i = 0; i < 5; ++i)
    {
        errFlag = QueueInsert(queue, i);
        if(errFlag != ERR_OK)
        {
            break;   
        }
    }

	PrintFormat(errFlag);
    printf("Test add normal\n");

	QueueDestroy(queue);
	return;
}

void TestAddVectorNull()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue = NULL;
    errFlag = QueueInsert(queue, 5);
	PrintFormat(!errFlag);
    printf("Test add to NULL\n");
    return;    
}

void TestAddMoreThanSize()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue;
    int i;
    queue = QueueCreate(QUEUE_SIZE);
    for(i = 0; i < QUEUE_SIZE + 5; ++i)
    {
        errFlag = QueueInsert(queue, i);
        if(errFlag != ERR_OK)
        {
            break;   
        }
    }

	PrintFormat(!errFlag);
    printf("Test add more than can contains\n");

	QueueDestroy(queue);
	return;
}

void TestDeleteNormal()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue;
    int i, tail;
    queue = QueueCreate(QUEUE_SIZE);
    for(i = 0; i < 5; ++i)
    {
        QueueInsert(queue, i);
    }
    
    errFlag = QueueRemove(queue, &tail);
    /*check if the value of the tail as expected*/
    if(tail != 0)
    {
        errFlag = 1;
    }
    PrintFormat(errFlag);
    printf("Test delete normal\n");
  	QueueDestroy(queue);
	return;
}

void TestDeleteTooMuch()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue;
    int i, tail;
    queue = QueueCreate(QUEUE_SIZE);
    for(i = 0; i < 5; ++i)
    {
        QueueInsert(queue, i);
    }
    
    for(i = 0; i < 15; ++i)
    {
        errFlag = QueueRemove(queue, &tail);
    }
 
	PrintFormat(!errFlag);
    printf("Test delete too much\n");
 	QueueDestroy(queue);
	return;
}

void TestDeleteIfQueueIsEmpty()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue;
    int tail;
    queue = QueueCreate(QUEUE_SIZE);
    errFlag = QueueRemove(queue, &tail);
	PrintFormat(!errFlag);
    printf("Test delete when array is empty\n");
 	QueueDestroy(queue);
	return;
}

void TestDeleteQueueNull()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue = NULL;
    int tail;
    errFlag = QueueRemove(queue, &tail);
	PrintFormat(!errFlag);
    printf("Test delete with NULL queue\n");
 	QueueDestroy(queue);
	return;
}

void TestDeleteAndAddInLoop()
{
    ADTErr errFlag = ERR_GENERAL;
    Queue* queue;
    int i, j, tail;
    queue = QueueCreate(QUEUE_SIZE);
    for(i = 0; i < 3; ++i)
    {
        QueueInsert(queue, i);
    }

    for(j = 0; j < 3; ++j)
    {
        for(i = 0; i < 6; ++i)
        {
            QueueInsert(queue, 8*j+i);
        }
        for(i = 0; i < 4; ++i)
        {
            QueueRemove(queue, &tail);
        }
    }
	PrintFormat(!errFlag);
    printf("Test delete and add in loop\n");
 	QueueDestroy(queue);
	return;
}


void PrintFormat(size_t _flag)
{
    if(_flag == 0)
    {
        printf("SUCCEEDED:  ");
    }
    else
    {
        printf("FAILED:     ");
    }
}






