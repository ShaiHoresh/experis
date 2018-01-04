#include <pthread.h>
#include <stdio.h>
#include <time.h>  /*seed*/
#include <stdlib.h> /* rand?! */

int g_temp = 23;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

#define NUM_OF_THREADS 100


void* AirConditioner(void* _something)
{
    
    
    pthread_mutex_lock(&mutex); 
    
    g_temp += ((rand() % 4) - 2);
    printf("sensor measured: %d\n", g_temp);
    pthread_cond_signal(&condition);
    
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

void* Sensor(void* _cont)
{
    pthread_mutex_lock(&mutex); 
    
    while(g_temp > 21 && g_temp < 25)
    {
        pthread_cond_wait(&condition, &mutex);
    }
    g_temp = 23;
    printf("aircond set temp to: %d\n", g_temp);
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}


int main()
{
    pthread_t sensors[NUM_OF_THREADS];
    pthread_t airconds[NUM_OF_THREADS];
    
    size_t i;
    
    srand((unsigned int)time(NULL));
    
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(&sensors[i], NULL, Sensor, NULL);
        pthread_create(&airconds[i], NULL, AirConditioner, NULL);
    }

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(sensors[i], NULL);
        pthread_join(airconds[i], NULL);
    }
    
    return 0;
}
