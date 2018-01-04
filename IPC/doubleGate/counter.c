/* includes */
#include <stdlib.h> /* atoi, abort*/
#include <string.h> /* strlen */
#include <unistd.h> /* write */
#include <stdio.h> /* sprintf, perror */
#include <pthread.h>
#include <time.h>   /* time */

#include "barrier.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int getID()
{
    static int count = -1;
    pthread_mutex_lock(&mutex);
    ++count;
    pthread_mutex_unlock(&mutex);
    return count;
}

typedef struct Params
{
    unsigned int     m_counter;
    unsigned int     m_iterations;
}Params;

int ParseOptions(Params* _par, int argc, char **argv);

/* threads structs and functions */

typedef struct SummarizerS
{
    Barrier*        m_barrier;
    unsigned int    m_counter;
    unsigned int    *m_array;
}SummarizerS;

int Summarize(void* _context)
{
    size_t i;
    unsigned int sum = 0;
    
    printf("\tIn summarizer\n");

    for(i = 0; i < ((SummarizerS*)_context)->m_counter; ++i)
    {
        sum += ((SummarizerS*)_context)->m_array[i];
    }
    return 0;
}

void* Summarizer(void* _context)
{
    printf("hello world!\n");
    BarrierWait(((SummarizerS*)_context)->m_barrier, Summarize, _context);
    
    pthread_exit(NULL);
}



typedef struct CounterS
{
    Barrier*        m_barrier;
    unsigned int    m_iterations;
    int             m_id;
    unsigned int    m_counter;
    unsigned int    *m_array;
}CounterS;

int CounterWork(void* _struct)
{
    int j;
    int me = ((CounterS*)_struct)->m_id; 
    printf("\tI'm in Counter\n");

    ((CounterS*)_struct)->m_array[me] = 0;
    
    for(j = 0; j < me; ++j)
    {
        ++((CounterS*)_struct)->m_array[me];
        usleep((unsigned int)(rand() % 100) * 1000);
    }
    return 0;
}

void* Counter(void* _struct)
{
    size_t i;
    ((CounterS*)_struct)->m_id = getID();

    for(i = 0; i < ((CounterS*)_struct)->m_iterations; ++i)
    {
        BarrierWait(((CounterS*)_struct)->m_barrier, CounterWork, _struct);
    }

    pthread_exit(NULL);
}

/* main function */
int main(int argc, char **argv)
{
    CounterS* counter;
    Params par = {5, 5};
    int *sum = NULL;
    unsigned int* array, summ;
    pthread_t *threads;
    size_t i;
    
    ParseOptions(&par, argc, argv);
    
    counter = malloc(sizeof(CounterS));
    if(NULL == counter)
    {
        return -1;
    }

    array = calloc(par.m_counter, sizeof(int));
    if(NULL == array)
    {
        return -1;
    }
    
    counter->m_barrier = BarrierCreate(par.m_counter);
    counter->m_iterations = par.m_iterations;
    counter->m_counter = par.m_counter;
    counter->m_array = array;
    threads = malloc((par.m_counter) * sizeof(pthread_t));
    if(NULL == threads)
    {
        return -1;
    }
    
    srand((unsigned int)time(NULL));
    
    for(i = 0; i < par.m_counter; ++i)
    {
        pthread_create(&threads[i], NULL, Counter, (void*)counter);
    }
    
    for(i = 0; i < par.m_counter; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    
    free(counter);
    free(array);
  /* free(threads);*/

    BarrierDestroy(counter->m_barrier);    
    
    
    /*
    create all counters
    
    in loop
        pthread create counter
        pthread join
        check sum and print it
    
    free structures
    destroy barrier (if works)
    */
    
    return 0;   
}









int ParseOptions(Params* _par, int argc, char **argv)
{
    int w;
    char info[] = "use flags: -c [num of counters], -i [num of iterations]";
    
    while((w = getopt(argc, argv, "c:i:")) != -1)
    {
        switch(w)
        {
            case 'c':
                _par->m_counter = (unsigned int)atoi(optarg);
                break;
            case 'i':
                _par->m_iterations = (unsigned int)atoi(optarg);
                break;
            case '?':
                write(STDOUT_FILENO, info, strlen(info)); 
            default:
                abort();
        }
    }
    
    return 1;
}
