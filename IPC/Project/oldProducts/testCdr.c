#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pdu.h"
#include "cdr.h"



int main()
{
    CDRData* cdr;
    Subscriber* sb;
    SubDS* sbArr;
    
    cdr = malloc(sizeof(CDRData));
    
    strcpy(cdr->m_imsi, "123456789012345");
    strcpy(cdr->m_msisdn, "098765432123456");
    strcpy(cdr->m_imei, "123456789009876");
    strcpy(cdr->m_operatorName, "Mycellolar");
    cdr-> m_tuple = 42512;
    cdr-> m_callType = MOC;
    strcpy(cdr->m_date, "11/11/11");
    strcpy(cdr->m_time, "14:23:34");
    cdr->m_duration = 123;
    cdr->m_download = 23.4;
    cdr->m_upload = 3.2;
    strcpy(cdr->m_corresMsisdn, "6483928474638");
    strcpy(cdr->m_corresOperatorName, "HisCellolar");


    sbArr = SubscriberCreateDS();
    
    sb = SubscriberGetData(cdr, sbArr);
    
    return 0;
}


