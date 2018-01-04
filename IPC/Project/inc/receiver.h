#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "pdu.h"
#include "comm.h"
    
typedef struct CdrData CdrData;

CDRData ReceiverGetCdr(CommData _comm); /* check params[in] */
 
#endif /* #ifndef __RECEIVER_H__ */
