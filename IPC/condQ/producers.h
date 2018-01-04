#ifndef __PRODUCERS_H__
#define __PRODUCERS_H__

typedef struct Producers Producers;

typedef void* UserFunction(void* _context); 

Producers* ProducersCreate(size_t _numOfProd);

void ProducersDestroy(Producers* _producers);

void* ProducerAction(void* _context);

void* PackAstruct(Queue* _question, Queue* _answer, Producers* _producers);

int InitAThreads(Producers* _producers, UserFunction _action, void* _context);

size_t ProducerJoin(Producers* _producers);


#endif /* __PRODUCERS_H__ */
