#include <string.h> /*strcpy*/
#include <stdlib.h> /*malloc*/
#include <stdio.h>

#include "PHashMap.h"

#include "pdu.h"
#include "subsStorage.h"

#define SIZE 1000000

struct SubsDS
{
    HashMap* m_storage;
};

typedef struct Subscriber
{
    unsigned int m_outGoingIn;
    unsigned int m_inComingIn;
    unsigned int m_outGoingOut;
    unsigned int m_inComingOut;
    unsigned int m_SMSoutGoingIn;
    unsigned int m_SMSinComingIn;
    unsigned int m_SMSoutGoingOut;
    unsigned int m_SMSinComingOut;
    unsigned int m_download;
    unsigned int m_upload;
}Subscriber;

/* Hashmap Functions 
unsigned int SubHash(const char* _key)
{
    unsigned int hash = 5381;
    int c = 0, i = 0;

    while(0 != (c = ((CDRData*)_key)->m_msisdn[i]))
    {
        hash = ((hash << 5) + hash) + c;
        i++;
    }
    return hash;
}
*/
static unsigned long SubHash(unsigned char *_key)
{
    unsigned long hash = 5381;
    int c;

    while(c = *_key++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}
/*
unsigned int SubHash(const void* _imsi)
{
    int sum;
    int i;
    sum = 0;
    for (i = 0; i < 17; ++i)
    {
        sum += (int)(((char*)_imsi)[i]);
    }
    return (size_t)sum;
}

*/
int SubEquality(const void* _firstKey, const void* _secondKey)
{
    if(strcmp((char*)_firstKey, (char*)_secondKey) == 0)
    {
        return 1;
    }
    return 0;
}

/*auxilary functions*/
static Subscriber* CreateSubscriber(SubsDS* _ds, CDRData* _data);

static int PushData(Subscriber* subscriber, CDRData* _data);

/*api function */
SubsDS* SubsDSCreate()
{
    SubsDS* ds;
    
    ds = malloc(sizeof(SubsDS*));
    if(!ds)
    {
        return NULL;
    }
    
    ds->m_storage = HashMapCreate(SIZE, (HashFunction)SubHash, SubEquality);
    if(!ds->m_storage)
    {
        return NULL;
    }
    
    printf("created Subcribers storage\n");
    
    return ds;
}
/*

static void PrintSubs(Subscriber* _sb, CDRData* _data)
{
    char buffer[1024];
    
    sprintf(buffer, "key: %s\noutin %u, inin %u, outout %u, inout %u, SMSoutin %u, SMSinin %u, SMSoutout %u, SMSinout %u, down %u, up %u\n", _data->m_msisdn, _sb->m_outGoingIn, _sb->m_inComingIn, _sb->m_outGoingOut, _sb->m_inComingOut, _sb->m_SMSoutGoingIn, _sb->m_SMSinComingIn, _sb->m_SMSoutGoingOut, _sb->m_SMSinComingOut, _sb->m_download, _sb->m_upload);
    puts(buffer);
}*/

int SubsUpdate(SubsDS* _ds, CDRData* _data)
{
    Map_Result res;
    Subscriber* subscriber;
    
    if(!_ds || !_data)
    {
        return -1;
    }
    
    HashMapLock(_ds->m_storage, (void*)_data->m_msisdn);
    res = HashMapFind(_ds->m_storage, (void*)_data->m_msisdn, (void**)&subscriber);
    if(res == MAP_SUCCESS)
    {
        PushData(subscriber, _data);
    }
    else
    {
        subscriber = CreateSubscriber(_ds, _data);
    }
    HashMapUnLock(_ds->m_storage, (void*)_data->m_msisdn);
    return 0;
}

static Subscriber* CreateSubscriber(SubsDS* _ds, CDRData* _data)
{
    Subscriber* subscriber;
    Map_Result ret;
    char* key;
    
    key = malloc(16 * sizeof(char));
    if(!key)
    {
        return NULL;
    }
    strcpy(key, _data->m_msisdn);
    
    subscriber = calloc(1, sizeof(Subscriber));
    if(!subscriber)
    {
        return NULL;
    }

    if(_data->m_tuple == _data->m_corresTuple)
    {
        switch(_data->m_callType)
        {
            case 0:
                subscriber->m_outGoingIn += _data->m_duration;
            break;
            case 1:
                subscriber->m_inComingIn += _data->m_duration;
            break;
            case 2: 
                subscriber->m_SMSoutGoingIn++;
            break;
            case 3:
                subscriber->m_SMSinComingIn++;
            break;
            default:
            break;
        }
    }
    else
    {
        switch(_data->m_callType)
        {
            case 0:
                subscriber->m_outGoingOut += _data->m_duration;
            break;
            case 1:
                subscriber->m_inComingOut += _data->m_duration;
            break;
            case 2:
                subscriber->m_SMSoutGoingOut++;
            break;
            case 3:
                subscriber->m_SMSinComingOut++;
            break;
            case 4:
                subscriber->m_download += _data->m_download;
                subscriber->m_upload += _data->m_upload;
            break;
            default:
            break;
        }
    }

    ret = HashMapInsert(_ds->m_storage, (void*)key, subscriber);
    if(ret != MAP_SUCCESS)
    {
        return NULL;
    }
    
    return subscriber;
}

static int PushData(Subscriber* _subscriber, CDRData* _data)
{
    if(_data->m_tuple == _data->m_corresTuple)
    {
        switch(_data->m_callType)
        {
            case 0:
                _subscriber->m_outGoingIn += _data->m_duration;
            break;
            case 1:
                _subscriber->m_inComingIn += _data->m_duration;
            break;
            case 2: 
                _subscriber->m_SMSoutGoingIn++;
            break;
            case 3:
                _subscriber->m_SMSinComingIn++;
            break;
            default:
            break;
        }
    }
    else
    {
        switch(_data->m_callType)
        {
            case 0:
                _subscriber->m_outGoingOut += _data->m_duration;
            break;
            case 1:
                _subscriber->m_inComingOut += _data->m_duration;
            break;
            case 2:
                _subscriber->m_SMSoutGoingOut++;
            break;
            case 3:
                _subscriber->m_SMSinComingOut++;
            break;
            case 4:
                _subscriber->m_download += _data->m_download;
                _subscriber->m_upload += _data->m_upload;
            break;
            default:
            break;
        }
    }
    return 1;
}

void Destroy(void* _something)
{
    free(_something);
}

void SubsDestroyDS(SubsDS* _ds)
{
    if(_ds)
    {
        HashMapDestroy(&(_ds->m_storage), Destroy, Destroy);
        free(_ds);
    }

}

int SubsPrint(char* _msisdn, Subscriber* _sb, void* _context)
{
    FILE* fd;
    
    fd = fopen("./Subscribers", "a");
    
    fprintf(fd, "%s: %u | %u | %u | %u | %u | %u | %u | %u | %u | %u\n", _msisdn, _sb->m_outGoingIn, _sb->m_inComingIn, _sb->m_outGoingOut, _sb->m_inComingOut, _sb->m_SMSoutGoingIn, _sb->m_SMSinComingIn, _sb->m_SMSoutGoingOut, _sb->m_SMSinComingOut, _sb->m_download, _sb->m_upload);

    fclose(fd);
    
    return 1;
}
    
    
    

int SubsGetOne(SubsDS* _ds, char* _msisdn)
{
    Map_Result res;
    Subscriber* subscriber;
    
    if(!_ds || !_msisdn)
    {
        return 0;
    }
    
    res = HashMapFind(_ds->m_storage, (void*)_msisdn, (void**)&subscriber);
    if(res == MAP_KEY_NOT_FOUND_ERROR)
    {
        return 0;
    }
    
    SubsPrint(_msisdn, subscriber, NULL);
    
    return 1;
}

int SubsGetAll(SubsDS* _ds)
{
    if(!_ds)
    {
        return 0;
    }
    
    fclose(fopen("./Subscribers", "w"));
    HashMapForEach(_ds->m_storage, (KeyValueActionFunction)SubsPrint, NULL);
    
    return 1;
}














