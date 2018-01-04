#ifndef __CDR_PDU_H__
#define __CDR_PDU_H__

typedef enum CallType
{
    MOC = 0,
    MTC,
    SMSMO,
    SMSMT,
    GPRS
}CallType ;

typedef struct CDRData
{
    char m_imsi[16];
    char m_msisdn[16];
    char m_imei[16];
    char m_operatorName[16];
    unsigned int  m_tuple;
    CallType m_callType;
    char m_date[16];
    char m_time[16];
    unsigned int m_duration;
    unsigned int m_download;
    unsigned int m_upload;
    char m_corresMsisdn[16];
    unsigned int m_corresTuple;
}CDRData;

#define TRIAL_SIZE 1000

#endif /* #define __CDR_PDU_H__ */
