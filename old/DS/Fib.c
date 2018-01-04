#include <stdio.h>
#include <string.h>

/*unsigned int RecFib(unsigned int _n);
unsigned int Fib(unsigned int _n);
unsigned int Factorial(unsigned int _n);*/
int RecIsPalindrome(char* _string, int _length);

int main()
{
/*    unsigned int i;
    
    printf("insert the index for Fibonacci and Factorial\n");
    scanf("%u", &i);
    printf("Fib of %u = %u\n", i, Fib(i));*/
    int isPal;
    char *string = "redivider";
    int length;
    length = strlen(string) - 1;
    
    isPal = RecIsPalindrome(string, length);
    printf("is the string %s is palindrome? %d\n", string, isPal); 
    
    return 0;
}
/*
unsigned int RecFib(unsigned int _n)
{
    if(_n == 0)
    {
        return 0;
    }
    if(_n == 1)
    {
        return 1;
    }
    
    return Fib(_n - 1) + Fib(_n - 2);
}

unsigned int Fib(unsigned int _n)
{
    unsigned int an1 = 0, an2 = 1, cur = 0, i = 0;

    for(i = 0; i < _n; ++i)
    {
        cur = an1 + an2;
        an2 = an1;
        an1 = cur;
    }
    return cur;
}

unsigned int Factorial(unsigned int _n)
{
    if(_n == 0)
    {
        return 1;
    }
    return (Factorial(_n - 1) * _n);
}*/

int RecIsPalindrome(char* _string, int _length)
{
    printf("%c =? %c\n", _string[0], _string[_length]);
    if(_length < 2)
    {
        return 1;
    }
    if(_string[0] != _string[_length])
    {
        return 0;
    }
    return RecIsPalindrome(_string + 1, _length - 2);
}


