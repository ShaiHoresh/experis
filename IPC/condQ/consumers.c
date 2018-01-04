#include <stdlib.h> /* malloc size_t */
#include <pthread.h> /* threads... */
#include <stdio.h> /* perror */
#include <errno.h>
#include <string.h> /* strcpy */
#include <unistd.h> /* usleep */

#include "queue.h"
#include "consumers.h"



struct Consumers
{
    pthread_t*      m_threadsArray;
    size_t          m_numOfCons;
    size_t          m_numOfCycles;
};

typedef struct QsWrapper
{
    Queue*      m_questions;
    Queue*      m_answers;
    Consumers*  m_consumers;
}QsWrapper;

void* PackQstruct(Queue* _question, Queue* _answer, Consumers* _consumers);


Consumers* ConsumersCreate(size_t _numOfCons, size_t _numOfCycles)
{
    /* declaration */
    Consumers* consumers;
    
    if(0 == _numOfCons || 0 == _numOfCycles)
    {
        return NULL;
    }
    
    /* allocations */
    consumers = malloc(sizeof(Consumers));
    if(NULL == consumers)
    {
        return NULL;
    }
    
    /* init struct */
    consumers->m_threadsArray = malloc(_numOfCons * sizeof(pthread_t));
    consumers->m_numOfCons = _numOfCons; /* Check if needed */
    consumers->m_numOfCycles = _numOfCycles; /* Check if needed */

    return consumers;
}    

void ConsumersDestroy(Consumers* _consumers)
{
    if(_consumers)
    {
        free(_consumers->m_threadsArray);
        free(_consumers);
    }
    return;
}
 
int InitCThreads(Consumers* _consumers, UserFunction _action, void* _context)
{
    size_t i;
    int ret;
    
    for(i = 0; i < _consumers->m_numOfCons; ++i)
    {
        ret = pthread_create(_consumers->m_threadsArray, NULL, _action, _context);
        if(ret)
        {
            free(_consumers->m_threadsArray);
            free(_consumers);
            perror("pthread create");
            exit(EXIT_FAILURE);
        }
    }
    return i;
}
    
/***************************************************************/


void* ConsumerAction(void* _context)
{
    size_t i;
    char* q = "What's up?";
    char* a = NULL;
    
    for(i = 0; i < ((QsWrapper*)_context)->m_consumers->m_numOfCycles; ++i)
    {
        QueueInsert(((QsWrapper*)_context)->m_questions, (void*)q);
        QueueRemove(((QsWrapper*)_context)->m_answers, (void**)&a); 
        usleep(100000);
        printf("in cons, printing: %s\n", a);
    }
    
    pthread_exit(NULL);
}

void* PackQstruct(Queue* _question, Queue* _answer, Consumers* _consumers)
{
    QsWrapper* qsWrapper;
    
    qsWrapper = malloc(sizeof(QsWrapper));
    if(NULL == qsWrapper)
    {
        return NULL;
    }
    
    qsWrapper->m_questions = _question;
    qsWrapper->m_answers = _answer;
    qsWrapper->m_consumers = _consumers;
    
    return (void*)qsWrapper;
}

size_t ConsumerJoin(Consumers* _consumers)
{
    size_t i;
    
    for(i = 0; i < _consumers->m_numOfCons; ++i)
    {
        pthread_join(_consumers->m_threadsArray[i], NULL);
    }
    return i;
}
/*
context -> consumers -> m_numOfCycles
context -> m_questions
context -> m_answers


struct Consumers
{
    pthread_t*      m_threadsArray;
    size_t          m_numOfCons;
    size_t          m_numOfCycles;
};

typedef struct QsWrapper
{
    Queue*      m_questions;
    Queue*      m_answers;
    Consumers*  m_consumers;
}QsWrapper;
*/

