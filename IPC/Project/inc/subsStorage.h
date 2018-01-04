#ifndef __SUBSSTORAGE_H__
#define __SUBSSTORAGE_H__

#include "pdu.h"

typedef struct SubsDS SubsDS;

SubsDS* SubsDSCreate();

int SubsUpdate(SubsDS* _ds, CDRData* _data);

int SubsGetOne(SubsDS* _ds, char* _msisdn);

int SubsGetAll(SubsDS* _ds);

void SubsDestroyDS(SubsDS* _ds);

#endif /* #ifndef __SUBSSTORAGE_H__ */
