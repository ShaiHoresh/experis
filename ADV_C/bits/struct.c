#include <stdio.h>

void iToB(int _num)
{
    int i, m = 1;
    m <<= sizeof(int) * 8 - 1;
    for(i = 0; i < sizeof(int) * 8; ++i)
    {
        (_num & m) != 0 ? printf("1 ") : printf("0 ");
        _num <<= 1;
    }
    printf("\n");
}

int Abs(int _num)
{
    int m = 1;
    
    m <<= sizeof(int) * 8 - 1;
    if((_num & m) != 0)
    {
        _num =~ _num + 1;
    }
    return _num;
}



void Dec2Hex(unsigned int _num)
{
    
    char hexArr[] =  {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    unsigned int i, m = 15, temp;
    
    m <<= 28;
    for(i = 0; i < 8; ++i)
    {
        temp = _num & m;
        temp >>= 28;
        printf("%c ", hexArr[temp]);
        _num <<= 4;
    }
    
    printf("\n");
    
}

int main()
{
    struct s1
    {
        int a;
        char b;
        int c;
        char d;
    };
    
    struct s2
    {
        char b;
        char d;
        int a;
        int c;
    };
    
    #pragma pack(push, 1) 
    struct s3
    {
        int a;
        int c;
        char b;
        char d;
    };
    #pragma pack(pop)
    unsigned char a = 254, b = 125;
    int c = 124, d;
    
    printf("s1 size = %lu\n", sizeof(struct s1));
    printf("s2 size = %lu\n", sizeof(struct s2));
    printf("s3 size = %lu\n", sizeof(struct s3));
    printf("%d-%d=%d, %d-%d=%d\n", a, b, a-b, a, b, (unsigned char)(a-b));
    /*swap in place*/
    printf("%d, %d\n", a, b);
    a ^= b;
    b ^= a;
    a ^= b;
    printf("%d, %d\n", a, b);
    
    printf("Abs\n");
    d = Abs(-c);    
    printf("abs(%d) = %d\n", -c, d);
    
    printf("\nhex\n");
    Dec2Hex(-c);
    iToB(-c);
    Dec2Hex(c);
    iToB(c);
}
