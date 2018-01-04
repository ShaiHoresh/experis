#ifndef __CDR_PROCESSOR_H__
#define __CDR_PROCESSOR_H__

typedef struct Operator Operator;
typedef struct Subscriber Subscriber;

#include "pdu.h"

typedef Hashmap OpDS;     /*temporary*/
typedef Subscriber* SubDS;  /*temporary*/

Subscriber* SubscriberGetData(CDRData* _data, SubDS *_arr);

Operator* OperatorGetData(CDRData* _data, OpDS *_opArr);

int SubscriberPushData(Subscriber* _SubData);

int OperatorPushData(Operator* _OpData);

SubDS* SubscriberCreateDS();  /* to be converted to hashmap */

OpDS* OperatorCreateDS();      /* to be converted to hashmap(?) */

void SubscriberDestroyDS(SubDS**);

void OperatorDestroyDS(OpDS**);

#endif /* #define __CDR_PROCESSOR_H__ */
