#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[])
{
    
    if(argc != 3)
    {
        printf("Invalid # of elements\n");
    }
    else if ((CheckNumber(argv[1]) && CheckName(argv[2])) ||
             (CheckNumber(argv[2]) && CheckName(argv[1])))
    {
        printf("Valid elements\n");
    }
    else
    {
        printf("Invalid elements\n");
    }
    
    return 0;
}


