#include <stdio.h>
#include <stdlib.h>

#include "feeder.h"
#include "parser.h"
#include "detector.h"


#define PATH "./"

void CDRprint(CDRData _dt, char* _buf)
{
    sprintf(_buf, "%s | %s | %s | %s | %u | %d | %s | %s | %u | %u | %u | %s | %u\n", _dt.m_imsi, _dt.m_msisdn, _dt.m_imei, _dt.m_operatorName, _dt.m_tuple ,_dt.m_callType , _dt.m_date, _dt.m_time, _dt.m_duration, _dt.m_download, _dt.m_upload, _dt.m_corresMsisdn, _dt.m_corresTuple);
    puts(_buf);
}

void SendData(CDRData* _context)
{
    CommData* comm;
    
    comm = CommCreate(NULL);
    if(!comm)
    {
        return;
    }
    PushData(comm, _context);
}

int main(int argc, char *argv[])
{
    CommData* comm;
    char* fileName;
    int i = 0;
    
    fileName = malloc(32 * sizeof(char));
    if(!fileName)
    {
        return -1;
    }
    
    comm = CommCreate(NULL);
    if(!comm)
    {
        return -1;
    }
    
    for(;; ++i)
    {
        if(NULL != Detect(PATH, &fileName))
        {
            printf("i = %d\n", i);
            ParseCdr(fileName, SendData);    
        }
    }
 
    return 0;
}
