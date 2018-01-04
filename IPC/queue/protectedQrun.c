#include <stdio.h>
#include <unistd.h>

#include "queue.h"
#include "consumers.h"
#include "producers.h"

#define Q_SIZE 5
#define PROD 7

int main (int argc, char **argv)
{
    Queue *answers, *questions;
/*    Params par;*/
    void *ques, *ans;
    Consumers* cons;
    Producers* prod;
    
/*    ParseOptions(&par, argc, argv);
*/    
    answers = QueueCreate(Q_SIZE);
    questions = QueueCreate(Q_SIZE);
    
    cons = ConsumersCreate(4, 4);
    prod = ProducersCreate(PROD);
    
    ques = PackQstruct(questions, answers, cons);
    ans = PackAstruct(questions, answers, prod);
    
    InitCThreads(cons, ConsumerAction, ques);
    InitAThreads(prod, ProducerAction, ans);
    
    printf("I'm here\n");
    ConsumerJoin(cons);
    ProducerJoin(prod);
    /* tell producers they should die */
    
/*    QueueDestroy();
    QueueDestroy();
    
    ConsumerDestroy();
    ProducerDestroy();
 */
    return 0;
}

/*

int RunConsumers(void* _data)
{
    Consumers* cons;
    void* data;
    
    cons = ConsumerCreate(5, 10);

    InitThreads(cons, Function, _data);
}*/


