#include <stdio.h>
#include <pthread.h>
#include <stddef.h>
#include <semaphore.h>

#define N 100 /*number of slots in the buffer*/

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER; /*controls access to critical region*/
sem_t empty; /*counts empty buffer slots*/
sem_t full; /*counts full buffer slots*/

int g_item = 0;

void* producer(void* tid)
{
    int item = 0, i = 0;
    while(i < 100000)         /*TRUE is the constant 1*/
    {
        item++;             /*generate something to put in buffer*/
        pthread_mutex_lock(&count_mutex);       /*enter critical region*/
        sem_wait(&empty);       /*decrement empty count*/
        g_item++;  /*put new item in buffer*/
        printf("In producer: item = %3d, g_item = %3d\n",item, g_item);
        pthread_mutex_unlock(&count_mutex);         /*leave critical region*/
        sem_post(&full);          /*increment count of full slots*/
        i++;
    }
    pthread_exit(tid);
}
void* consumer(void* tid)
{
    int item = 0, i = 0;
    while(i < 100000)         /*TRUE is the*/
    {                   /*infinite loop*/
        item++;
        pthread_mutex_lock(&count_mutex);       /*enter critical region*/
        sem_wait(&full);        /*decrement full count*/
        g_item--;            /*take item from buffer*/
        printf("In consumer: item = %3d, g_item = %3d\n",item, g_item);         /*do something with the item*/
        pthread_mutex_unlock(&count_mutex);         /*leave critical region*/
        sem_post(&empty);         /*increment count of empty slots*/
        i++;
    }
    pthread_exit(tid);
}

int main()
{
    int thread1, thread2;
    pthread_t threads[2];

    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    thread1 = pthread_create(&threads[1], NULL, producer, NULL);
    thread2 = pthread_create(&threads[2], NULL, consumer, NULL);
    
    pthread_exit(NULL);
    
    return 0;
}
