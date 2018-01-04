#include <stdio.h>
#include <pthread.h>
#include <stddef.h>
#include <semaphore.h>

#define N 100 /*number of slots in the buffer*/

sem_t mutex; /*controls access to critical region*/
sem_t empty; /*counts empty buffer slots*/
sem_t full; /*counts full buffer slots*/

int g_item = 0;

void producer(void* tid)
{
    int item;
    while(1)        /*TRUE is the constant 1*/
    {
        item++;             /*generate something to put in buffer*/
        sem_wait(&empty);       /*decrement empty count*/
        sem_wait(&mutex);       /*enter critical region*/
        g_item++;  /*put new item in buffer*/
        printf("In producer: item = %d, g_item = %d\n",item, g_item);
        sem_post(&mutex);         /*leave critical region*/
        sem_post(&full);          /*increment count of full slots*/
    }
    pthread_exit(tid);
}
void consumer(void* tid)
{
    int item;
    while(1) 
    {                   /*infinite loop*/
        item++;
        sem_wait(&full);        /*decrement full count*/
        sem_wait(&mutex);       /*enter critical region*/
        g_item--;            /*take item from buffer*/
        printf("In consumer: item = %d, g_item = %d\n",item, g_item);         /*do something with the item*/
        sem_post(&mutex);         /*leave critical region*/
        sem_post(&empty);         /*increment count of empty slots*/
    }
    pthread_exit(tid);
}

int main()
{
    int thread1, thread2;
    pthread_t threads[2];
    sem_init(&mutex,0,1);
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    thread1 = pthread_create(&threads[1], NULL, producer, NULL);
    thread2 = pthread_create(&threads[2], NULL, consumer, NULL);
    
    pthread_exit(NULL);
    
    return 0;
}
