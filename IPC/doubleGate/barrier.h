#ifndef __BARRIER_H__
#define __BARRIER_H__

typedef struct Barrier Barrier;

typedef int(*CallBack)(void*);

Barrier* BarrierCreate(unsigned int _capacity);

void BarrierDestroy(Barrier* _barrier);

int BarrierWait(Barrier* _barrier, CallBack _cb, void* _context);

#endif /* #ifndef __BARRIER_H__ */
