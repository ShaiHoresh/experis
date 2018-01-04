#ifndef __OPERSRORAGE_H__
#define __OPERSRORAGE_H__

#include "pdu.h"

typedef struct OperDS OperDS;

OperDS* OperDSCreate();

int OperUpdate(OperDS* _ds, CDRData* _data);

int OperGetOne(OperDS* _ds, unsigned int _tuple);

int OperGetAll(OperDS* _ds);                    /* not implemented yet */

void OperDestroyDS(OperDS* _ds);

#endif /* #ifndef __OPERSRORAGE_H__ */
