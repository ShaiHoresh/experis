#include <stdio.h>
#include "Strings.h"

/* recursive core of StrLen, has to get 0 for returning the right num of characters in str */
static size_t StrLenRecIn(const char* _str, size_t _i);

/* recursive core of StrCompare*/
static int StrCompareRecIn(const char* _s1, const char* _s2);

static void StrCopyRecIn(char* _destination, const char* _source);
static void StrNCopyRecIn(char* _destination, const char* _source, size_t _num);

int main()
{
    const char* str = "shalom al Israel";
    char* s2 = "shalom, How are you?";
    char s3[64], s4[64], s5[64];
    char s6[64] = "shi ";
    char s7[64] = "horesh";
    char* s8 = "How";
    
    printf("%d\n", StrLen(str));
    printf("%d\n", StrLenRec(str));
    printf("%d\n", StrCompare(str, s2));
    printf("%d\n", StrCompareRec(str, s2));
    StrCopy(s3, str);
    printf("s3 = %s\n", s3);
    StrCopyRec(s3, s2);
    printf("s3 = %s\n", s3);
    
    printf("s4 = %s\n", StrNCopy(s4, s2, 10));
    printf("s5 = %s\n", StrNCopyRec(s5, s2, 10));
    printf("My name is %s\n", StrConcat(s6, s7));
    printf("%s\n", StrSubString(s2, s8));
    
    return 0;   
}

size_t StrLen(const char* _str)
{
    size_t i = 0;
    
    if(NULL == _str)
    {
        return 0;
    }
    
    while(_str[i] != '\0')
    {
        ++i;
    }
    return i;
}

size_t StrLenRec(const char* _str)
{
    if(NULL == _str)
    {
        return 0;
    }
    
    return StrLenRecIn(_str, 0);
}

int StrCompare(const char* _s1, const char* _s2)
{
    int i = 0;
    if(NULL == _s1 || NULL == _s2)
    {
        return _s1 - _s2;
    }
    while(_s1[i] != '\0' && _s2[i] != '\0')
    {
        if(_s1[i] - _s2[i] != 0)
        {
            break;
        }
        ++i;
    }
    return _s1[i] - _s2[i];
}

int StrCompareRec(const char* _s1, const char* _s2)
{
    if(NULL == _s1 || NULL == _s2)
    {
        return 0;
    }
    return StrCompareRecIn(_s1, _s2); 
}

char* StrCopy(char* _destination, const char* _source)
{
    int i = 0;
    
    if(NULL == _destination || NULL == _source)
    {
        return NULL;
    }
    while(_source[i] != '\0')
    {
        _destination[i] = _source[i];
        ++i;
    }
    _destination[i] = '\0';
    return _destination;
}
char* StrCopyRec(char* _destination, const char* _source)
{
    char *copy = _destination;
    if(NULL == _destination || NULL == _source)
    {
        return 0;
    }
    StrCopyRecIn(_destination, _source);
    return copy;
}

char* StrNCopy(char* _destination, const char* _source, size_t _num)
{
    int i = 0;
    
    if(NULL == _destination || NULL == _source)
    {
        return NULL;
    }
    while(i < _num && _source[i] != '\0')
    {
        _destination[i] = _source[i];
        ++i;
    }
    _destination[i] = '\0';
    return _destination;
}

char* StrNCopyRec(char* _destination, const char* _source, size_t _num)
{
    char *copy = _destination;
    if(NULL == _destination || NULL == _source)
    {
        return 0;
    }
    StrNCopyRecIn(_destination, _source, _num);
    return copy;
}

char* StrConcat(char* _destination, const char* _source)
{
    size_t destLen;
    if(NULL == _destination || NULL == _source)
    {
        return 0;
    }
    destLen = StrLen(_destination);
    StrCopy(_destination + destLen, _source);
    return _destination;
}

char* StrSubString(char* _str, const char* _search)
{
    size_t i, j, strLen, searchLen;
    int flag = 1;
    strLen = StrLen(_str);
    searchLen = StrLen(_search);
    
    for(i = 0; i + searchLen < strLen; ++i)
    {
        if(_str[i] == _search[0])
        {
            for(j = 0; j < searchLen; ++j)
            {
                if(_str[i + j] != _search[j])
                {
                    flag = 0;
                }
            }
            if(flag == 1)
            {
                break;
            }
        }
    }
    return _str + i;
}

/*************************Aux functions**********************/
static void StrNCopyRecIn(char* _destination, const char* _source, size_t _num)
{
    if(*_source == '\0' || _num == 0)
    {
        *_destination = '\0';
        return;
    }
    *_destination = *_source;
    StrNCopyRecIn(_destination + 1, _source + 1, _num - 1);
    return;
}

static void StrCopyRecIn(char* _destination, const char* _source)
{
    if(*_source == '\0')
    {
        *_destination = '\0';
        return;
    }
    *_destination = *_source;
    StrCopyRecIn(_destination + 1, _source + 1);
    return;
}

static int StrCompareRecIn(const char* _s1, const char* _s2)
{
    if(*_s1 - *_s2 != 0 || *_s1 == '\0')
    {
        return *_s1 - *_s2;
    }
    StrCompareRec(_s1 + 1, _s2 + 1);
}

static size_t StrLenRecIn(const char* _str, size_t _i)
{
    if(_str[_i] == '\0')
    {
       return _i;
    }
    StrLenRecIn(_str, ++_i);
}

