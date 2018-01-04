#include <stdio.h>
#define NDEBUG
#include <assert.h>


int main()
{
    int a;
    printf("enter a number\n");
    scanf("%d", &a);
    
    assert(a < 5);
    
    printf("after assert\n");
    
    return 0;
}
