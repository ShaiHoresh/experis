#include <stdio.h> /*FILE*/
#include <string.h> /*strcmp*/
#include <stdlib.h> /*atoi*/

#include "feeder.h"
#include "parser.h"
#include "pdu.h"



void ParseCdr(char* _fileName, CBack _cb)
{
    /* dec */
    FILE* fp;
    CDRData cdr;
    char buffer[256];
    char call[8], dur[8], dow[8], up[8], tu[8];

    /* check */
    if(!_fileName)
    {
        return;
    }

    /* open file */
    fp = fopen(_fileName, "r");
    if(NULL == fp)
    {
        return;
    }
    printf("started parsing\n");
    
    memset(&cdr, 0, sizeof(CDRData));

    fgets(buffer, sizeof(buffer), fp);

    /* parse */
    while(fgets(buffer, sizeof(buffer), fp))
    {
        sscanf(buffer, "%16[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%u", cdr.m_imsi, cdr.m_msisdn, cdr.m_imei,  cdr.m_operatorName, tu, call, cdr.m_date, cdr.m_time, dur, dow, up, cdr.m_corresMsisdn, &cdr.m_corresTuple);
        if(strcmp(call, "MOC") == 0) cdr.m_callType = MOC;
        if(strcmp(call, "MTC") == 0) cdr.m_callType = MTC;
        if(strcmp(call, "SMSMO") == 0) cdr.m_callType = SMSMO;
        if(strcmp(call, "SMSMT") == 0) cdr.m_callType = SMSMT;
        if(strcmp(call, "GPRS") == 0) cdr.m_callType = GPRS;
        cdr.m_duration = atoi(dur);
        cdr.m_download = atoi(dow);
        cdr.m_upload = atoi(up);
        cdr.m_tuple = atoi(tu);
        
        _cb(&cdr);
        memset(&cdr, 0, sizeof(CDRData));
    }
    /* return(?) */
}

