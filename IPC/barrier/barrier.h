#ifndef __BARRIER_H__
#define __BARRIER_H__

typedef struct Barrier Barrier;

Barrier* BarrierCreate(unsigned int _capacity);

void BarrierDestroy(Barrier* _barrier);

int BarrierWait(Barrier* _barrier);

#endif /* #ifndef __BARRIER_H__ */
