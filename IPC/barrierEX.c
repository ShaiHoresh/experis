#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "barrier/barrier.h"

Barrier* barrier;
/*pthread_barrier_t barrier;*/

void* ThreadFunc(void* _context)
{
    int id = *(int*)_context;
    printf("thread number %d started\n", id);
    sleep(id);
    printf("thread number %d woke up\n", id);
    
/*    pthread_barrier_wait(&barrier);*/
    BarrierWait(barrier);
    printf("thread number %d is going\n", id);
    
    pthread_exit(NULL);
}

int main()
{
    int i, arr[4];
    pthread_t thrds[4];
    
    
    /*pthread_barrier_init(&barrier, NULL, 5);*/
    barrier = BarrierCreate(4);
    
    for(i = 0; i < 4; ++i)
    {
        arr[i] = i % 4;
        pthread_create(&thrds[i], NULL, ThreadFunc, &arr[i]);
        sleep(i);
    }
    
   /* pthread_barrier_wait(&barrier);*/
    BarrierDestroy(barrier);
    
    sleep(15);
    
    for(i = 0; i < 4; ++i)
    {
        pthread_join(thrds[i], NULL);
    }    
    
/*    pthread_barrier_destroy(&barrier);*/
    
    return 0;
}
