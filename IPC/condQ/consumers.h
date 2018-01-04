#ifndef __CONSUMERS_H__
#define __CONSUMERS_H__

typedef struct Consumers Consumers;

typedef void* UserFunction(void* _context);

Consumers* ConsumersCreate(size_t _numOfCons, size_t _numOfCycles);

void ConsumersDestroy(Consumers* _consumers);

void* ConsumerAction(void* _context);

int InitCThreads(Consumers* _consumers, UserFunction _action, void* _context);

void* PackQstruct(Queue* _question, Queue* _answer, Consumers* _consumers);

size_t ConsumerJoin(Consumers* _consumers);


#endif /* __CONSUMERS_H__ */
