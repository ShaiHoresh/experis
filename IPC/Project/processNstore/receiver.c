#include <stdlib.h> /* malloc */

#include "receiver.h"
#include "pdu.h"

CDRData ReceiverGetCdr(CommData _comm)
{
    CDRData data;
        
    PullData(&_comm, &data);
    
    return data;
}


