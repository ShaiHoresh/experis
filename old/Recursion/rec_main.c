#include <stdio.h>
#include "rec_ex.h"

int main()
{
    int array[5] = {2, 4, 6, 8, 13};
    char string[3] = "abc";
    
    TopPyramid(5);
    printf("\n");
    BottomPyramid(5);
    printf("\n");
    printf("%f",Average(array, 5));
    printf("\n");
    printf("\n%c\n", LastChar("Shalom Al Israel"));
    printf("\n");
    MultiTable(10);
    printf("\n");
    Perm(string, 5);
    return 0;
}

