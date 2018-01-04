#include <stdio.h>
#include <unistd.h>

#include "queue.h"
#include "consumers.h"
#include "producers.h"

#define Q_SIZE 10
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
    
    cons = ConsumersCreate(10, 4);
    prod = ProducersCreate(PROD);
    
    ques = PackQstruct(questions, answers, cons);
    ans = PackAstruct(questions, answers, prod);
    
    InitCThreads(cons, ConsumerAction, ques);
    InitAThreads(prod, ProducerAction, ans);
    
    ConsumerJoin(cons);
    ProducerJoin(prod);
    
    QueueDestroy(answers);
    QueueDestroy(questions);

    ConsumersDestroy(cons);
    ProducersDestroy(prod);

    return 0;
}


