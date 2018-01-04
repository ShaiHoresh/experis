#include <stdlib.h>
#include <stdio.h>
#include "Bytes.h"

static int IsBitOn(unsigned char _x, int _p);
static unsigned char BitOff(unsigned char _x, int _p);
static unsigned char BitOn(unsigned char _x, int _p);

/*All function should use bit wise operations only*/

unsigned char invert(unsigned char _x)
{
    unsigned char y;
    
    y = 255^_x;
    PrintBinChar(y);
    return y;
}

unsigned char rotate(unsigned char _x, int _numRot)
{
    int val = 0, i, msb = 1;
    msb <<= BYTESIZE - 1;
    for(i = 0; i < _numRot; ++i)
    {
        val = _x % 2;
        _x >>= 1;
        if(val == 1)
        {
            _x |= msb;
        }
    }
    PrintBinChar(_x);
    return _x;
}

unsigned char SetBit(unsigned char _x, int _p, int _n, unsigned char _y)
{
    int i;
    
    if(_p > BYTESIZE || _n > BYTESIZE || BYTESIZE - _n > _p)
    {
        return 0;
    }
    
    for(i = 0; i < _n; ++i)
    {
        if(IsBitOn(_y, i) == 1)
        {
            _x = BitOn(_x, _p - _n + i);
        }
        else
        {
            _x = BitOff(_x, _p - _n + i);
        }
    }
    return _x;
}

static unsigned char BitOn(unsigned char _x, int _p)
{
    unsigned char ch = 1;
    
    ch <<= _p;
    _x = (_x | ch);
    return _x;
}

static unsigned char BitOff(unsigned char _x, int _p)
{
    unsigned char ch = 1;
    
    ch <<= _p;
    if(_x ==(_x | ch))
    {
        _x ^= ch;
    }
    return _x;
}

static int IsBitOn(unsigned char _x, int _p)
{
    int flag = 0;
    unsigned char ch = 1;
    ch <<= _p;
    
    if(_x == (_x | ch))
    {
        flag = 1;
    }
    return flag;
}

unsigned int SetBits(unsigned int _w, int _i, int _j, int _value)
{
    int index;
    unsigned int scr = 1;
    
    if(_i < 0 || _i >= INTSIZE || _j < 0 || _j >= INTSIZE || _j < _i)
    {
        return 0;
    }
    for(index = 0; index < (_j - _i); ++index)
    {
        scr = ((scr << 1) | 1);
    }
    scr <<= (_i - 1);

    _value == 1 ? _w |= scr : (_w &= (~scr));
    
    return _w;
}

void PrintBinChar(unsigned char _x)
{
    int i = 0;
    for(i = 0; i < BYTESIZE; ++i)
    {
        printf("%d ", _x % 2);
        _x /= 2;
    }
    printf("\n");
}

void PrintBinInt(unsigned int _x)
{
    int i = 0;
    for(i = 0; i < 4*BYTESIZE; ++i)
    {
        printf("%d ", _x % 2);
        _x /= 2;
    }
    printf("\n");
}

