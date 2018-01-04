#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>

#include "string_t.h"

#define DEFCAPACITY 16

// static fields declaration
size_t String_t::classCapacity = DEFCAPACITY;
bool String_t::caseSens = false;
size_t String_t::numOfStrings = 0;

void String_t::CreateFrom(const char* _str)
{
    length = strlen(_str);
    myCapacity = classCapacity;
    
    while(length > myCapacity)
    {
        myCapacity *= 2;
    }
    
    if(length > classCapacity)
    {
        delete[] str;
    }
    str = new char[myCapacity];
    
    if(0 == str)
    {
        //TODO
    }
    strcpy(str, _str);
}


String_t::String_t()
{
    CreateFrom("\0");
    ++numOfStrings;
}

String_t::~String_t()
{
    --numOfStrings;
    delete[] str;
}

String_t::String_t(const String_t& _src)
{
    if(this != &_src)
    {
        CreateFrom(_src.str);
    }
    ++numOfStrings;
}

String_t::String_t(const char* _src)
{
    _src ? CreateFrom(_src) : CreateFrom('\0');
    ++numOfStrings;
}

const String_t& String_t::operator=(const String_t& _str)
{
    if(this != &_str)
    {
        CreateFrom(_str.str);
    }
    
    return *this;
}



int String_t::Set(const char* _new)
{
    if(_new)
    {
        CreateFrom(_new);
        return 1;
    }
    
    return 0;
}

int String_t::Compare(const String_t& _cmp) const
{
    int dif;
    
    if(caseSens == true)
    {
        dif = strcmp(str, _cmp.str);
    }
    else
    {
        dif = strcasecmp(str, _cmp.str);
    }
    
    return dif == 0 ? 0 : dif < 0 ? 1 : 2;
}



void String_t::Upper()
{
    int len = strlen(str);
    
    for(int i = 0; i < len; ++i)
    {
        str[i] = (char)toupper(str[i]);
    }
}

void String_t::Lower()
{
    int len = strlen(str);
    
    for(int i = 0; i < len; ++i)
    {
        str[i] = (char)tolower(str[i]);
    }
}

void String_t::Prepend(const char* _pre)
{
    if(!_pre)
    {
        //TODO
    }
    
    int len = strlen(_pre) + strlen(str) + 1;
    char* copy;
    copy = new char[len];
    if(0 == copy)
    {
        //TODO
    }
    
    strcpy(copy, _pre);
    strcat(copy, str);
    delete[] str;
    str = new char[len];
    if(0 == str)
    {
        //TODO
    }
    strcpy(str, copy);
    delete[] copy;
}

void String_t::Prepend(const String_t& _pre)
{
    int lenPre = _pre.Length();
    int len = strlen(str) + lenPre;
    char* copy;
    copy = new char[len + 1];
    if(0 == copy)
    {
        //TODO
    }
    
    strcpy(copy, _pre.Get());
    strcat(copy, str);
    delete[] str;
    str = new char[len];
    if(0 == str)
    {
        //TODO
    }
    strcpy(str, copy);
    delete[] copy;
}

bool String_t::Contains(const char* _sub) const
{
    if(!_sub || strlen(str) < strlen(_sub))
    {
        return false;
    }
    
    if(caseSens == true)
    {
        return strstr(str, _sub) ? true : false;
    }
    else
    {
        return strcasestr(str, _sub) ? true : false;
    }
}

const String_t& String_t::operator+=(const String_t& _str)
{
    int len = strlen(str) + strlen(_str.str) + 1;
    
    char* copy = new char[len];
    if(0 == str)
    {
        //TODO
    }
    
    strcpy(copy, str);
    strcat(copy, _str.str);
    
    delete[] str;
    
    str = copy;
    
    return *this;
}

const bool String_t::operator<(const String_t& _str)
{
    int check = Compare(_str);
    return check == 1 ? true : false;
}

const bool String_t::operator>(const String_t& _str)
{
    int check = Compare(_str);
    return check == 2 ? true : false;
}

const bool String_t::operator>=(const String_t& _str)
{
    int check = Compare(_str);
    return (check == 0 || check == 1) ? true : false;
}

const bool String_t::operator<=(const String_t& _str)
{
    int check = Compare(_str);
    return (check == 2 || check == 0) ? true : false;
}

const bool String_t::operator==(const String_t& _str)
{
    int check = Compare(_str);
    return check == 0 ? true : false;
}

const bool String_t::operator!=(const String_t& _str)
{
    int check = Compare(_str);
    return check != 0 ? true : false;
}

ostream& operator<<(ostream& os, const String_t& _str)
{
    os << "the string is: " << _str.Get() << "\n";
    
    return os;
}

istream& operator>>(istream& is, String_t& _str)
{
    char string[128];
    
    is >> string;
    _str.Set(string);
    
    return is;
}

const char String_t::operator[](size_t _index)
{
    return _index > strlen(str) ? '\0' : str[_index];
}

int String_t::FirstOccurrence(const char _c) const
{
    char* match;
    
    if(caseSens)
    {
        match = strchr(str, _c);
    }
    else
    {
        char upperC = (char)toupper(_c);
        for(unsigned int i = 0; i < length; ++i)
        {
            if(upperC == str[i] || upperC == (char)toupper(str[i]))
            {
                match = &str[i];
                break;
            }
        }
    }
    
    return match ? (match - str) : -1;
}

int String_t::LastOccurrence(const char _c) const
{
    char* match;
    unsigned int i;
    
    if(caseSens)
    {
        for(i = 0; i < length; ++i)
        {
            if(_c == str[i])
            {
                match = &str[i];
            }
        }
    }
    else
    {
        char upperC = (char)toupper(_c);
        for(i = 0; i < length; ++i)
        {
            if(upperC == str[i] || upperC == (char)toupper(str[i]))
            {
                match = &str[i];
            }
        }
    }
    
    return match ? (match - str) : -1;
}

String_t String_t::operator()(int _start, unsigned int _len)
{
    if((unsigned int)_start > length)
    {
        String_t();
    }
    else if(_len + (unsigned int)_start > (unsigned int)length)
    {
        String_t(str + _start);
    }    
    return String_t(str + _start, _len);
}

String_t::String_t(const char* _str, unsigned int _len)
{
    CreateFromN(_str, _len);
    ++numOfStrings;
}

void String_t::CreateFromN(const char* _str, unsigned int _len)
{
    length = strlen(_str);
    myCapacity = classCapacity;
    
    while(length > myCapacity)
    {
        myCapacity *= 2;
    }
    
    if(length > classCapacity)
    {
        delete[] str;
    }
    str = new char[myCapacity];
    
    if(0 == str)
    {
        //TODO
    }
    strncpy(str, _str, _len);
}






