#include <stdlib.h>
#include <stdio.h>
#include "Bytes.h"

#define BYTESIZE 8
void PrintBitMap(bitMap* _bM);
void PrintBitMap2(bitMap* _bM);
static int Check(bitMap* _bM, int _bitNum);

bitMap* CreateBitMap(unsigned int _nof)
{
    bitMap* bM;
    int numOfChars;
    
    bM = malloc(sizeof(bitMap));
/*    if(_nof % BYTESIZE == 0)
    {
        numOfChars = _nof / BYTESIZE;
    }
    else
    {
        numOfChars = _nof / BYTESIZE + 1;
    }*/
    numOfChars = _nof / BYTESIZE + (_nof % BYTESIZE != 0);
    if(NULL == bM)
    {
        return NULL;
    }
    bM->bits = calloc(numOfChars, sizeof(char));
    if(NULL == bM->bits)
    {
        free(bM);
        return NULL;
    }
    bM->nof = _nof;

    return bM;
}

int DestroyBitMap(bitMap* _bM)
{
    if(!_bM)
    {
        free(_bM->bits);
    }
    free(_bM);
    return 1;
}

int BitOn(bitMap* _bM, int _bitNum)
{
    int byteIndex, bitIndex;
    unsigned char ch = 1;
    
    --_bitNum;
    
    if(!Check(_bM, _bitNum))
    {
        return 0;
    }
    
    byteIndex = _bitNum / 8;
    bitIndex = _bitNum % 8;
    
    ch <<= bitIndex;
    
    _bM->bits[byteIndex] |= ch;
    
    return 1;
}

int BitOff(bitMap* _bM, int _bitNum)
{
    int byteIndex, bitIndex;
    unsigned char ch = 1;
    
    --_bitNum;
    
    if(!Check(_bM, _bitNum))
    {
        return 0;
    }
    
    byteIndex = _bitNum / BYTESIZE;
    bitIndex = _bitNum % BYTESIZE;
    
    ch <<= bitIndex;
    
    if(_bM->bits[byteIndex] == (_bM->bits[byteIndex] | ch))
    {
        _bM->bits[byteIndex] ^= ch;
    }
        
    return 1;
}

int IsBitOn(bitMap* _bM, int _bitNum)
{
    unsigned char ch = 1, flag = 0;
    --_bitNum;
    
    if(!Check(_bM, _bitNum))
    {
        return -1;
    }

    ch <<= _bitNum % BYTESIZE;
    
    if(_bM->bits[_bitNum / BYTESIZE] == (_bM->bits[_bitNum / BYTESIZE] | ch))
    {
        flag = 1;
    }
        
    return flag;
}

void PrintBitMap(bitMap* _bM)
{
    int i, j, counter, res;
    counter = 0;
    
    for(i = 0; i < (_bM->nof / BYTESIZE) + 1 ; ++i)
    {
        res = _bM->bits[i];
        for(j = 0; j < BYTESIZE; ++j)
        {
            if(counter == _bM->nof)
            {
                break;
            }
            printf("%d ", res % 2);
            res /= 2;
            ++counter;
        }
    }
    printf("\n\n");
}

void PrintBitMap2(bitMap* _bM)
{
    int i;
    for(i = 1; i <= _bM->nof; ++i)
    {
        printf("%d ", IsBitOn(_bM, i));
    }
    printf("\n\n");
}

static int Check(bitMap* _bM, int _bitNum)
{
    return(!(NULL == _bM || NULL == _bM->bits || _bitNum > _bM->nof || _bitNum < 0));
}
