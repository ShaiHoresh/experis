#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "main.h"

int CheckNumber(char* _num)
{
    int len, i, number;
    
    len = strlen(_num);
    for(i = 0; i < len; ++i)
    {
        if(!isdigit(_num[i]))
        {
            return 0;
        }
    }
    number = atoi(_num);
    return number;
    
}

int CheckName(char* _name)
{
    int len, i, res = 0;
   
    len = strlen(_name);
    if(isupper(_name[0]))
    {
        res = 1;
    }
    
    for(i = 1; i < len; ++i)
    {
        if(!islower(_name[i]))
        {
            return 0;
        }
    }
    return res;
}






















