#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "comm.h"
#include "receiver.h"
#include "operStorage.h"
#include "subsStorage.h"

void CDRprint(CDRData _dt)
{
    char buffer[1024];
    sprintf(buffer, "m_imsi - %s,\nm_msisdn - %s,\nm_imei - %s,\nm_operatorName - %s,\nm_tuple - %u,\nm_callType - %d,\nm_date - %s,\nm_time - %s,\nm_duration - %u,\nm_download - %u,\nm_upload - %u,\nm_corresMsisdn - %s,\nm_corresTuple - %u\n", _dt.m_imsi, _dt.m_msisdn, _dt.m_imei, _dt.m_operatorName, _dt.m_tuple ,_dt.m_callType, _dt.m_date, _dt.m_time, _dt.m_duration, _dt.m_download, _dt.m_upload, _dt.m_corresMsisdn, _dt.m_corresTuple);
    puts(buffer);
}

int main()
{
    CommData* comm;
    int i;
    CDRData data;
    SubsDS* sb;
    OperDS* op;
    
    comm = CommCreate(NULL);
    sb = SubsDSCreate();
    op = OperDSCreate();
    
    if(!comm || !sb || !op)
    {
        printf("something failed...\n");
        return -1;
    }
    
    for(i = 0; i < 10000000; ++i)
    {
        data = ReceiverGetCdr(*comm);
        SubsUpdate(sb, &data);
        OperUpdate(op, &data);
        if(i % 10000 == 0)
        {
            printf("inserted %d cdrs\n", i);
        }
    }
    
    printf("generating operators report...\n");
    OperGetAll(op);
    printf("operators report created.\ngenerating subscribers report...\n");
    SubsGetAll(sb);
    printf("subscribers report created\n");
    /*
    printf("42501: ");
    OperGetOne(op, a);
    
    printf("42503: ");
    OperGetOne(op, c);
*/
    printf("\n");
    
    CommClose(comm);
    
    return 0;
}
