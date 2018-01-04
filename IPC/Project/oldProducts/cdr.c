#include <string.h> /*strcpy*/
#include <malloc.h>

#include "HashMap.h"

#include "pdu.h"

#define ARRAY_SIZE 10

struct Subscriber
{
    char* m_msisdn;
    unsigned int m_outGoingIn;
    unsigned int m_inGoingIn;
    unsigned int m_outGoingOut;
    unsigned int m_inGoingOut;
    unsigned int m_SMSoutGoingIn;
    unsigned int m_SMSinGoingIn;
    unsigned int m_SMSoutGoingOut;
    unsigned int m_SMSinGoingOut;
    unsigned int m_download;
    unsigned int m_upload;
};

struct Operator
{
    unsigned int m_tuple;
    unsigned int m_outGoing;
    unsigned int m_inGoing;
    unsigned int m_SMSoutGoing;
    unsigned int m_SMSinGoing;
};

static Subscriber* SubscriberCreate(char* m_msisdn);

static Operator* OperatorCreate(unsigned int  m_tuple);

static void SubPrint(Subscriber* _sb) /* other fields will be added for debugging */
{
    printf("%s|\n", _sb->m_msisdn);
}

Subscriber* SubscriberGetData(CDRData* _data, Subscriber* *_arr) /* TEMPORARY!!! */
{
    size_t i;
    Subscriber* sb;
    
    for(i = 0; i < ARRAY_SIZE; ++i)
    {
        if(_arr[i]->m_msisdn)
        {
            if(strcmp(_data->m_msisdn, _arr[i]->m_msisdn) == 0)
            {
                return _arr[i];
            }
        }
    }
    
    sb = SubscriberCreate(_data->m_msisdn);
    SubPrint(sb);
    return sb;
}

Operator* OperatorGetData(CDRData* _data, Operator* *_opArr)
{
    size_t i;
    Operator* op;
    
    for(i = 0; i < ARRAY_SIZE; ++i)
    {
        if(_data->m_tuple == _opArr[i]->m_tuple)
        {
            return _opArr[i];
        }
    }
    
    op = OperatorCreate(_data->m_tuple);
    
    return op;
}

static Subscriber* SubscriberCreate(char* m_msisdn)
{
    /*dec*/    
    Subscriber* sbData;
    
    /*check*/
    if(!m_msisdn)
    {
        return NULL;
    }
    
    /*alloc*/
    sbData = malloc(sizeof(Subscriber));
    if(!sbData)
    {
        return NULL;
    }
    
    /*init*/
    strcpy(sbData->m_msisdn, m_msisdn);
    sbData->m_outGoingIn = 0;
    sbData->m_inGoingIn = 0;
    sbData->m_outGoingOut = 0;
    sbData->m_inGoingOut = 0;
    sbData->m_SMSoutGoingIn = 0;
    sbData->m_SMSinGoingIn = 0;
    sbData->m_SMSoutGoingOut = 0;
    sbData->m_SMSinGoingOut = 0;
    sbData->m_download = 0;
    sbData->m_upload = 0;
    
    /*ret*/
    return sbData;
}

static Operator* OperatorCreate(unsigned int  m_tuple)
{
    Operator* OpData;
    
    /*check*/
    if(!m_tuple)
    {
        return NULL;
    }
    
    /*alloc*/
    OpData = malloc(sizeof(Operator));
    if(!OpData)
    {
        return NULL;
    }
    
    OpData->m_tuple = m_tuple;
    OpData->m_outGoing = 0;
    OpData->m_inGoing = 0;
    OpData->m_SMSoutGoing = 0;
    OpData->m_SMSinGoing = 0;
    
    return OpData;
}

int SubscriberPushData(Subscriber* _SubData);

int OperatorPushData(Operator* _OpData);

size_t SubHash(void* _key)
{
    unsigned long hash = 5381;
    int c;

    while(0 != (c = *((Subscriber*)_key)->m_msisdn++))
    {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }
    return (size_t)hash;
}

size_t OpHash(void* _key)
{
    return ((Operator*)_key)->m_tuple;
}

int Equality(const void* _firstKey, const void* _secondKey)
{
    return strcmp((const char*) _firstKey, (const char*) _secondKey);
}

SubDS* SubscriberCreateDS(unsigned int size)         /*temporary array*/
{
    return HashMapCreate(size, SubHash, Equality);
}

OpDS* OperatorCreateDS(unsigned int size)            /*temporary array*/
{
    return HashMapCreate(size, OpHash, Equality);
}

void SubscriberDestroyDS();

void OperatorDestroyDS();

void SubscriberDestroy(Subscriber*);

void OperatorDestroy(Operator*);

