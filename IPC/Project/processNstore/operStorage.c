#include <string.h> /*strcpy*/
#include <stdlib.h>
#include <stdio.h>


#include "PHashMap.h"

#include "pdu.h"
#include "operStorage.h"

#define SIZE 30

struct OperDS
{
    HashMap* m_storage;
};

typedef struct Operator
{
    unsigned int m_outGoing;
    unsigned int m_inComing;
    unsigned int m_SMSoutGoing;
    unsigned int m_SMSinComing;
}Operator;

/* Hashmap Function (very very simple) */
size_t Hash(unsigned int* _key)
{
    return (size_t)*_key;
}

int Equality(const void* _firstKey, const void* _secondKey)
{
    if (*(int*)_firstKey == *(int*)_secondKey)
    {
        return 1;
    }
    return 0;
}

/*auxilary functions*/
static Operator* CreateInsertOperator(OperDS* _ds, CDRData* _data);

static int PushData(Operator* operator, CDRData* _data);

int OperPrint(Operator* _operator);

/*api function */

OperDS* OperDSCreate()
{
    OperDS* ds;
    
    ds = malloc(sizeof(OperDS));
    if(!ds)
    {
        return NULL;
    }
    
    ds->m_storage = HashMapCreate(SIZE, (HashFunction)Hash, Equality);
    if(!ds->m_storage)
    {
        return NULL;
    }
    
    printf("created Operators storage\n");
    
    return ds;
}
/*
static void PrintOper(Operator* _op)
{
    char buffer[1024];
    
    sprintf(buffer, "out %u, in %u, sms out %u, sms in %u\n", _op->m_outGoing, _op->m_inComing, _op->m_SMSoutGoing, _op->m_SMSinComing);
    puts(buffer);
}*/

int OperUpdate(OperDS* _ds, CDRData* _data)
{
    /* declarations */
    Map_Result res;
    Operator* operator;
    
    /* checks */
    if(!_ds || !_data)
    {
        return -1;
    }
    
    if(_data->m_tuple == _data->m_corresTuple || _data->m_callType == GPRS)
    {
        return 0;
    }
    
    HashMapLock(_ds->m_storage, (void*)&_data->m_corresTuple);
    
    /* find and aggregate */
    res = HashMapFind(_ds->m_storage, (void*)&_data->m_corresTuple, (void**)&operator);
    if(res == MAP_SUCCESS)
    {
        PushData(operator, _data);
    }
    else
    {
        operator = CreateInsertOperator(_ds, _data);
    }
    HashMapUnLock(_ds->m_storage, (void*)&_data->m_corresTuple);
    
    return 0;
}

static Operator* CreateInsertOperator(OperDS* _ds, CDRData* _data)
{
    Operator* operator;
    Map_Result ret;
    unsigned int* key;
    
    key = malloc(sizeof(unsigned int));
    if(!key)
    {
        return NULL;
    }
    *key = _data->m_corresTuple;
    
    operator = calloc(1, sizeof(Operator));
    if(NULL == operator)
    {
        return NULL;
    }

    if (_data->m_tuple != _data->m_corresTuple)
    {
        switch(_data->m_callType)
        {
            case 0:
                operator->m_outGoing += _data->m_duration;
            break;
            case 1:
                operator->m_inComing += _data->m_duration;
            break;
            case 2:
                operator->m_SMSoutGoing++;
            break;
            case 3:
                operator->m_SMSinComing++;
            break;
            default:
            break;
        }
    }
    
    ret = HashMapInsert(_ds->m_storage, (void*)key, (void*)operator);
    if(ret != MAP_SUCCESS)
    {
        return NULL;
    }
    
    return operator;    
}

static int PushData(Operator* operator, CDRData* _data)
{
    if (_data->m_tuple != _data->m_corresTuple)
    {
        switch(_data->m_callType)
        {
            case 0:
                operator->m_outGoing += _data->m_duration;
            break;
            case 1:
                operator->m_inComing += _data->m_duration;
            break;
            case 2:
                operator->m_SMSoutGoing++;
            break;
            case 3:
                operator->m_SMSinComing++;
            break;
            default:
            break;
        }
    }
    
    return 1;
}


int OperGetOne(OperDS* _ds, unsigned int _tuple)
{
    /* declarations */
    Map_Result res;
    Operator* operator;
    
    /* checks */
    if(!_ds)
    {
        return 0;
    }
    
    /* find and aggregate */
    res = HashMapFind(_ds->m_storage, (void*)&_tuple, (void**)&operator);
    if(res == MAP_KEY_NOT_FOUND_ERROR)
    {
        return 0;;
    }
    
    /* print (to file?) data */
    OperPrint(operator);
    
    return 1;
}

int OpPrintToFile(unsigned int* _key, Operator* _operator, void* _context)
{
    FILE* fd;
    
    fd = fopen("./Operators", "a");
    
    fprintf(fd, "tuple %u: m_outGoing %u, m_inComing %u, m_SMSoutGoing %u, m_SMSinComing %u,\n", *_key, _operator->m_outGoing, _operator->m_inComing, _operator->m_SMSoutGoing, _operator->m_SMSinComing);
    
    fclose(fd);
    return 1;
}

int OperGetAll(OperDS* _ds)
{
    if(!_ds)
    {
        return -1;
    }
    
    fclose(fopen("./Operators", "w"));
    HashMapForEach(_ds->m_storage, (KeyValueActionFunction)OpPrintToFile, NULL);
    
    return 1;
}

int OperPrint(Operator* _operator)
{
    char buffer[1024];
    sprintf(buffer, "m_outGoing %u,\nm_inComing %u,\nm_SMSoutGoing %u,\nm_SMSinComing %u,\n", _operator->m_outGoing, _operator->m_inComing, _operator->m_SMSoutGoing, _operator->m_SMSinComing);
    puts(buffer);
    
    return 1;
}

void Destroy2(void* _something)
{
    free(_something);
}

void OperDestroyDS(OperDS* _ds)
{
    if(_ds)
    {
        HashMapDestroy(&(_ds->m_storage), Destroy2, Destroy2);
        free(_ds);
    }

}
