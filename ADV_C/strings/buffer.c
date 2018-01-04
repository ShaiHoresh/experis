#include <stdio.h>

int g_add;

int Hack(int _y)
{
    printf("in hack\n");
    *(&_y - 1) = g_add;
    return 0;
}

int Foo(int x)
{
    int i = 5;
    printf("in Foo: &x = %p, val = %d\n", &x, x);
    printf("in Foo: &x - 1 = %p, val = %p\n", &x - 1, *(&x - 1));
    printf("in Foo: &x - 2 = %p, val = %p\n", &x - 2, *(&x - 2));
    printf("in Foo: &x - 3 = %p, val = %p\n", &x - 3, *(&x - 3));
    printf("in Foo: &x - 4 = %p, val = %p\n", &x - 4, *(&x - 4));
    printf("in Foo: &x - 5 = %p, val = %p\n", &x - 5, *(&x - 5));
    printf("in Foo: &x - 6 = %p, val = %d\n", &x - 6, *(&x - 6));
    printf("in Foo: &i = %p, i = %d\n", &i, i);
    
    g_add = *(&x - 1);
    *(&x - 1) = (int)Hack;

    return 1;
}


int main()
{
    int n = 5;
    printf("from main to foo\n");
    Foo(n);
    printf("return to main\n");
}
