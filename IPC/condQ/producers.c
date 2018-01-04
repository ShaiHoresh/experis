#include <stdlib.h> /* malloc, size_t */
#include <string.h> /* strcpy */
#include <pthread.h>
#include <errno.h> /* errno */
#include <stdio.h> /* perror */
#include <unistd.h> /* DEBUGGING usleep */

#include "queue.h"
#include "producers.h"


typedef struct AnsWrapper 
{
    Queue*      m_questions;
    Queue*      m_answers;
    Producers*  m_producers;
}AnsWrapper;

struct Producers
{
    pthread_t*      m_threadsArray;
    size_t          m_numOfProducers;
};

Producers* ProducersCreate(size_t _numOfProducers)
{
    /* declaration */
    Producers* producers;
    
    if(0 == _numOfProducers)
    {
        return NULL;
    }
    
    /* allocations */
    producers = malloc(sizeof(Producers));
    if(NULL == producers)
    {
        return NULL;
    }
    
    /* init struct */
    producers->m_threadsArray = malloc(_numOfProducers * sizeof(pthread_t));
    producers->m_numOfProducers = _numOfProducers; /* Check if needed */

    return producers;
}

void ProducersDestroy(Producers* _producers)
{
    if(_producers)
    {
        free(_producers->m_threadsArray);
        free(_producers);
    }
    return;
}

int InitAThreads(Producers* _producers, UserFunction _action, void* _context)
{
    int i;
    int ret;
    
    for(i = 0; i < _producers->m_numOfProducers; ++i)
    {
        ret = pthread_create(_producers->m_threadsArray, NULL, _action, _context);
        if(ret)
        {
            free(_producers->m_threadsArray);
            free(_producers);
            perror("pthread create");
            exit(EXIT_FAILURE);
        }
    }
    return i;
}

void* ProducerAction(void* _context)
{
    char* q = "and how are you?";
    char* a = NULL;
    
    for(;;)
    {
        if(QueueIsEmpty(((AnsWrapper*)_context)->m_answers) == 0)
        {
            usleep(2000);
        }
        if(QueueIsEmpty(((AnsWrapper*)_context)->m_answers) == 0 && QueueIsEmpty(((AnsWrapper*)_context)->m_questions) == 0)
        {
            break;
        }
        
        QueueRemove(((AnsWrapper*)_context)->m_questions, (void**)&a);
        printf("in prod, printing: %s\n", a);
        usleep(1000);
        QueueInsert(((AnsWrapper*)_context)->m_answers, (void*)q);
    }
    
    pthread_exit(NULL);    
}

void* PackAstruct(Queue* _question, Queue* _answer, Producers* _producers)
{
    AnsWrapper* ansWrapper;
    
    ansWrapper = malloc(sizeof(AnsWrapper));
    if(NULL == ansWrapper)
    {
        return NULL;
    }
    
    ansWrapper->m_questions = _question;
    ansWrapper->m_answers = _answer;
    ansWrapper->m_producers = _producers;
    
    return (void*)ansWrapper;
}

size_t ProducerJoin(Producers* _producers)
{
    size_t i;
    
    for(i = 0; i < _producers->m_numOfProducers; ++i)
    {
        pthread_join(_producers->m_threadsArray[i], NULL);
    }
    return i;
}



/*

typedef struct AnsWrapper 
{
    Queue*      m_questions;
    Queue*      m_answers;
    Consumers*  m_consumers;
}AnsWrapper;

struct Producers
{
    pthread_t*      m_threadsArray;
    size_t          m_numOfProducers;
};
*/
