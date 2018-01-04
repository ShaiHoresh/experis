#include <stdio.h>
#include "rec_ex.h"

static int PrintTable(unsigned int _x, unsigned int _y, unsigned int _n);

void TopPyramid(unsigned int _num)
{
    int i;
    if(_num == 0) return;
    TopPyramid(_num - 1);
    for(i = 0; i < _num; ++i)
    {
        printf("*");
    }
    printf("\n");
}

void BottomPyramid(unsigned int _num)
{
    int i;
    if(_num == 0) return;
    for(i = 0; i < _num; ++i)
    {
        printf("*");
    }
    printf("\n");
    BottomPyramid(_num - 1);
}

float Average(int* _array, unsigned int _size)
{
    float sum;
    if(0 == _size)  return 0;

    
    sum = ((Average(_array, _size - 1) * (_size - 1)) + _array[_size - 1]) / _size;


    return sum;
}

char LastChar(char* _string)
{
    if(NULL == _string) return ' ';
    if(_string[1] == '\0')
    {
        return _string[0];
    }
    LastChar(_string + 1);
}

int MultiTable(unsigned int _n)
{
    if(0 == _n) return 0;
    PrintTable(1, 1, _n);
    return 1;
}

static int PrintTable(unsigned int _x, unsigned int _y, unsigned int _n)
{
    if(_y <= _n)
    {
        printf("%3d ", _x * _y);
        if(_x <= _n)
        {
            return PrintTable(_x , _y + 1, _n);
        }
    }
    printf("\n");
    if(_x == _n) return 0;
    PrintTable(_x + 1, 1, _n);
    return 1;
}

int Perm(char* _string, unsigned int _length)
{
    if(_length == 1) return 0;
    printf("%s\n", _string);
    
}







