/* includes */
#include <stdlib.h> /* atoi, abort*/
#include <string.h> /* strlen */
#include <unistd.h> /* write */
#include <stdio.h> /* sprintf, perror */
#include <pthread.h>
#include <time.h>   /* time */

#include "barrier.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int getID()
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

void* Summarizer(void* _struct)
{
    size_t i;
    unsigned int sum = 0;
    
    BarrierWait(((SummarizerS*)_struct)->m_barrier);
    
    for(i = 0; i < ((SummarizerS*)_struct)->m_counter; ++i)
    {
        sum += ((SummarizerS*)_struct)->m_array[i];
    }
    BarrierWait(((SummarizerS*)_struct)->m_barrier);
    
    pthread_exit(&sum);
}

typedef struct CounterS
{
    Barrier*        m_barrier;
    unsigned int    m_iterations;
    unsigned int    m_counter;
    unsigned int    *m_array;
}CounterS;

void* Counter(void* _struct)
{
    size_t i, j;
    size_t id = getID(); 

    for(i = 0; i < ((CounterS*)_struct)->m_iterations; ++i)
    {
        ((CounterS*)_struct)->m_array[id] = 0;
        
        for(j = 0; j < id; ++j)
        {
            ++((CounterS*)_struct)->m_array[id];
            usleep((rand() % 1000) * 1000);
        }
        
        BarrierWait(((CounterS*)_struct)->m_barrier);
        BarrierWait(((CounterS*)_struct)->m_barrier);
    }

    pthread_exit(NULL);
}

/* main function */
int main(int argc, char **argv)
{
    SummarizerS* summarizer;
    CounterS* counter;
    Params par = {5, 5};
    int *sum = NULL, summ;
    unsigned int* array;
    pthread_t *threads;
    size_t i;
    
    ParseOptions(&par, argc, argv);
    
    summarizer = malloc(sizeof(SummarizerS));
    if(NULL == summarizer)
    {
        return -1;
    }
        
    counter = malloc(sizeof(CounterS));
    if(NULL == counter)
    {
        return -1;
    }
    
    summarizer->m_barrier = BarrierCreate(par.m_counter + 1);
    if(NULL == summarizer->m_barrier)
    {
        return -1;
    }
    
    array = calloc(par.m_counter + 1, sizeof(int));
    if(NULL == array)
    {
        return -1;
    }
    
    summarizer->m_array = array;
    summarizer->m_counter = par.m_counter;
    
    counter->m_barrier = summarizer->m_barrier;
    counter->m_iterations = par.m_iterations;
    counter->m_counter = par.m_counter;
    counter->m_array = array;
    threads = malloc((par.m_counter + 1) * sizeof(pthread_t));
    if(NULL == threads)
    {
        return -1;
    }
    
    srand(time(NULL));
    
    for(i = 0; i < par.m_counter; ++i)
    {
        pthread_create(&threads[i], NULL, Counter, (void*)counter);
    }
    
    summ = (par.m_counter - 1) * par.m_counter / 2;
    for(i = 0; i < par.m_iterations; ++i)
    {
        pthread_create(&threads[par.m_counter + 1], NULL, Summarizer, (void*)summarizer);
        pthread_join(threads[par.m_counter + 1], (void**)&sum);
        printf("[calculate] %u =? %u [return from summarizer]\n", summ, *sum);
    }
   
    free(summarizer);
    free(counter);
    free(array);
  /* free(threads);*/

    BarrierDestroy(summarizer->m_barrier);    
    
    
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
                _par->m_counter = atoi(optarg);
                break;
            case 'i':
                _par->m_iterations = atoi(optarg);
                break;
            case '?':
                write(STDOUT_FILENO, info, strlen(info)); 
            default:
                abort();
        }
    }
    
    return 1;
}
