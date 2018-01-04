#include <stdio.h>
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

int g_val;

void *PrintFunc(void* threadid)
{
    long tid;
    int i = 5;
    tid = (long) threadid;

    printf("%ld, %d\n", tid, (void*)&tid);

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[1000];
    size_t i = 0;
    int status;
    
    while(1)
    {
        status = pthread_create(&threads[i], NULL, PrintFunc, (void*)i);
        ++i;
        if(status)
        {
            printf("succeed %d threads\n", i);
            break;
        }
    }

    for(i = 0; i < 10; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
}


