

#include "PrimPrintf.h"

int main()
{
    int i = 1, j = 2, k = 3;
    char ch1[] = "Shalom", ch2[] = "bla bla", ch3[] = "qq";
    float f1 = 3.14, f2 = 1.41, f3 = 1.618;

    MyPrintf("Hello = %s, the %% val (%d) of PI is %f", f2, ch1, j, f1);
    MyPrintf("%d part of %f = %s, right?", i, f3, ch2);
    MyPrintf("%s, I have a Q: is %d^2 = (%d + %d)? A: Well, YES %s!!!", ch1, j, k, i, ch3);
    return 0;
}

