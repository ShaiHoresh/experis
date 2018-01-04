#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "PrimPrintf.h"

int MyPrintf(const char* sen, ...)
{
    char toPrint[1024] = {0}, tempCh[128];
    int intPar, i = 0, len, counter = 0;
    char *charPar/*[128]*/;
    double doublePar;
        
    va_list args;
    va_start(args, sen);
    len = strlen(sen);
    toPrint[0] = '\0';

    while(i < len)
    {
        if(sen[i] == '%')
        {
            ++i;
            switch(sen[i])
            {
                case 'd':
                    intPar = va_arg(args, int);
                    sprintf(tempCh, "%d", intPar);
                    counter += strlen(tempCh);
                break;
                case 'f':
                    doublePar = va_arg(args, double);
                    sprintf(tempCh, "%f", doublePar);
                    counter += strlen(tempCh);
                break;
                case 's':
                    printf("%c\n", sen[i]);
                    charPar = va_arg(args, char*);
                    printf("%s\n", charPar);
                    sprintf(tempCh, "%s", charPar);
                    printf("%s\n", tempCh);
                    counter += strlen(tempCh);
                break;
                case '%':
                    *tempCh = '%';
                    ++counter;
                break;
                default:
                    puts("!!problematic input!!\n");
                    return 0;
                break;
            }
            strcat(toPrint, tempCh);
            ++i;
        }
        toPrint[counter] = sen[i];
        ++i;    
        ++counter;
    }

    va_end(args);
    puts(toPrint);
    return strlen(toPrint);
}
