#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    char *ptr;
    
    ptr = malloc(1024 * 1024 * sizeof(char));
    printf("%p\n", &i);
    printf("%p\n", ptr);
    while(ptr != NULL)
    {
        ++i;
        ptr = malloc(1024 * 1024 * sizeof(char));
        printf("%p\n", ptr);
    }
    printf("%d mallocs seucceeded\n", i);
    
    return 0;
}
