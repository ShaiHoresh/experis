#include <stdlib.h>/*malloc and size t*/
#include <pthread.h>/*thread*/
#include <stdio.h>/*printf*/
#include <time.h>/*srand*/
#include <unistd.h>/*usleep and getopt*/

#include "barrier.h"



 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



typedef struct Input
{
    unsigned int m_numOfCounter;/*number of counting threat to create */
    unsigned int m_numOfIter;/*number of iteration each thread will preform*/
    unsigned int m_numOfMessages;/*num of message to send*/ 
}Input;



typedef struct CounterData
{
    int* m_arr; /*where to insert the write the number of messages sent by each thread */
    Barrier* m_barrier;/*pointer to the barrier*/ 
    unsigned int m_numOfIter;/*number of iteration need to preform*/
    unsigned int m_numOfMessages; /*number of messages to "send"*/  
}CounterData;




typedef struct SumData
{
    int* m_arr;/*where to insert the write the number of messages sent by each thread */
    Barrier* m_barrier; 
    unsigned int m_numOfIter; /*num of times to check the array*/
    unsigned int m_numOfCounter; /*size of the array*/  
    unsigned int m_sum; 
}SumData;



/**  
 * @brief Parsing gets the input string and "braek it down" to deferent argument  
 * @param[in] _input - pointer to the input struct
 * @param[in] argc - number of argument inserted
 * @param[in] *argv - pointer to string ware the string instored
 * @return void
 * @warning sets default value if the usuer didnt insert deferent ones;. 
 */
void Parsing(Input* _input , int argc, char* *argv)
{
    int  opt;
    _input -> m_numOfIter = 5;
    _input -> m_numOfCounter = 5;
    _input -> m_numOfMessages =15;
    
     while ((opt = getopt(argc, argv, "i:c:n:")) != -1) 
    {
        switch (opt)
        {
        case 'i':
            _input -> m_numOfIter = atoi(optarg);
        break;
        case 'c':
            _input -> m_numOfCounter = atoi(optarg);
        break;
        case 'n':
            _input -> m_numOfMessages = atoi(optarg);
        break;
   
        default: /* '?' */
        fprintf(stderr, "Usage: %s [-n ]numOfmessages [-s] num of servers [-c]num of client \n",
                argv[0]);
        exit(EXIT_FAILURE);
        }
    }
    return ;
}


/**  
 * @brief GetId gives each thread unique id number base on the order he got to the func    
 * @param[in] void
 * @return int - number that represent id for the thread usually the number represent index in array
 */   
int GetId()
{
    static int count =-1;
    pthread_mutex_lock(&mutex);
    count++;
    pthread_mutex_unlock(&mutex);
    return count;
}



/**  
 * @brief the function initial the counter struct that will be send to the counting thread
 * @param[in] *_counterData - pointer to the struct to be fulled
 * @param[in] *_input - pointer to the user inserted input
 * @param[in] *_barrier - pointer to the barrier
 * @param[in] *_count - pointer to the array the write the num of messages the tread send
 * @return *_counterData - pointer to the struct;
 * @warning cant get NULL pointers
 */
CounterData* CounterInit(CounterData* _counterData,Input* _input,Barrier* _barrier,int* _count)
{
    _counterData -> m_arr =_count;
    _counterData -> m_barrier = _barrier ;
    _counterData -> m_numOfIter =_input -> m_numOfIter;
    _counterData -> m_numOfMessages =_input -> m_numOfMessages;

    return _counterData;
}

/**  
 * @brief the function initial the data struct that will be send to the summarizer thread
 * @param[in] *_sumData - pointer to the struct to be fulled
 * @param[in] *_input - pointer to the user inserted input
 * @param[in] *_barrier - pointer to the barrier
 * @param[in] *_count - pointer to the array to sum the number in it
 * @return *SumData - pointer to the struct;
 * @warning cant get NULL pointers
 */
SumData* SumInit(SumData* _sumData,Input* _input,Barrier* _barrier,int* _count)
{
    _sumData -> m_arr = _count;
    _sumData -> m_barrier = _barrier;
    _sumData -> m_numOfIter = _input -> m_numOfIter;
    _sumData -> m_numOfCounter = _input -> m_numOfCounter;
    _sumData -> m_sum =0;
    return _sumData;
}


int Sum(void* _context)  
{
    int i;
    (((SumData*)_context) ->m_sum)=0;
    for(i=0; i<((SumData*)_context)->m_numOfCounter; i++)
    {
       (((SumData*)_context) ->m_sum) += (((SumData*)_context) ->m_arr[i]);
       (((SumData*)_context) ->m_arr[i])=0;     
    }
    return (((SumData*)_context) ->m_sum);
}


/**  
 * @brief the summarizer is the thread runnig routine, the func sum the num of message in the arre and return the value
 * @param[in] *_context - void pointer to the data strunc 
 * @return *void - null - the data sent by the struct it self;
 * @warning to use the struct member beed to cast to SumData*
 */
void* summarizer(void* _context)  
{   
    printf("summarizer id: %u\n", GetId());
    BarrierWait( (((SumData*)_context) ->m_barrier),Sum, _context);
    pthread_exit(NULL);
}
/***************************************************************************************************/




/**  
 * @brief the counter is the thread runnig routine, the func send number of messages in incres
 * the value in her on cell in the arrey by using the id it got from the function GetId() as a index
 * @param[in] *_context - void pointer to the data strunc 
 * @return *void - null - the data sent by the struct it self;
 */
void* counter (void* _context)
{
    int i,j,id;
    id = GetId();
    printf("\tmy id is %u\n",id);
    for(i=0; i< (((CounterData*)_context) ->m_numOfIter); i++)
    {
        
        for(j=0; j<(((CounterData*)_context) ->m_numOfMessages); j++)
        {
            ((CounterData*)_context) -> m_arr[id]++;
             usleep((rand()%100)*1000);      
        }
        printf("\tim counter number: %u\n",id);
        BarrierWait( (((CounterData*)_context) ->m_barrier),NULL,NULL);
    }      
    return NULL;
}

/*****************************************************/
int main(int argc, char *argv[])
{
    Input* input;/*struct for the input data*/
    int i,j,rc;/*i and j are indexs for the loops and rc flage for the ptread create*/
    int* count; /*array for the num of message*/  
    pthread_t* threadList;/*array of thread*/
    CounterData* counterData;
    SumData* sumData;
    Barrier* barrier;
    
    srand(time(NULL));
    
    input = malloc(sizeof(Input));
    
    Parsing(input ,argc,argv);
    
    count = malloc(input->m_numOfCounter*sizeof(int));
    if(!count)
    {
        return 0;
    }
    
    threadList = malloc((input->m_numOfCounter+1)*sizeof(pthread_t));
    
    if(!threadList)
    {
        free(count);
        return 0;
    }
    
    
    
    counterData = malloc(sizeof(CounterData));
    if(!counterData)
    {
        free(count);
        free(threadList);
        return 0;
    }
    
    sumData = malloc(sizeof(SumData));
    if(!sumData)
    {
        free(count);
        free(threadList);
        free(counterData);
        return 0;
    }
    
    barrier = BarrierCreate(input->m_numOfCounter+1);
    if(!barrier)
    {
        free(count);
        free(threadList);
        free(counterData);
        free(sumData);
        return 0; 
    }
    counterData = CounterInit(counterData,input,barrier,count);
    
    sumData = SumInit(sumData,input,barrier,count);
     
   
    /*create the counter treads*/
    for(i=0; i < input->m_numOfCounter; i++)
    { 
        rc = pthread_create(&threadList[i], NULL, counter,(void*)counterData);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    /*create the summarizer tread*/
    for(j=0; j < input->m_numOfIter; j++)
    { 
        
        rc = pthread_create(&threadList[i], NULL, summarizer,(void*)sumData);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        pthread_join((threadList[i]),NULL);
        
        if(sumData -> m_sum == (input->m_numOfCounter*input->m_numOfIter) )
        {
            printf("pass: the nam of message received is %d out of %d sent\n",sumData -> m_sum, (input->m_numOfCounter*input->m_numOfIter));
        }
    }
    
    
    BarrierDestroy(barrier);
    pthread_mutex_destroy(&mutex);/*mutex for the GetId func*/
    free(count);
    free(threadList);
    free(counterData);
    free(sumData);
}
