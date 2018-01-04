#include <string.h>
#include <cctype>
#include <stdexcept>
#include <iostream>

#include "String.h"
namespace advcpp
{

String::String()
{
    m_str[0] = '\0';
}

String::String(const char* _data)
{
    if(_data)
    {
        Buffer<char> temp(*(char*)_data, strlen(_data) + 1);
//        std::size_t len = strlen(_data);
//        m_str(*_data, len);
        m_str = temp;
    }
}

String::String(const String&_other)
{
    m_str = _other.m_str;
}

String::~String()
{
}

String& String::operator=(const String& _other) 
{
    if(this != &_other)
    {
        m_str = _other.m_str;
    }
    
    return *this;
}

String& String::operator=(const char* _other) 
{
    if(_other)
    {
        m_str = Buffer<char>(*_other, strlen(_other) + 1);
    }
    
    return *this;
}

bool String::operator==(const char* _other) const
{
    if(_other)
    {
        return !strcmp(m_str.GetData(), _other);
    }
    
    return false;
}

bool String::operator==(const String& _other) const
{
    return !strcmp(m_str.GetData(), _other.m_str.GetData());
}

bool String::operator!=(const String& _other) const
{
    return strcmp(m_str.GetData(), _other.m_str.GetData());
}

bool String::operator!=(const char* _other) const
{
    return strcmp(m_str.GetData(), _other);
}

const char String::operator[](std::size_t _index) const
{
    if(Length() - 1 < _index)
    {
        throw std::out_of_range("out of range");
    }
    return (m_str.GetData())[_index];
}

char String::operator[](std::size_t _index)
{
    if(Length() - 1 < _index)
    {
        throw std::out_of_range("out of range");
    }
    return (m_str.GetData())[_index];
}


String String::operator+(const String& _second) const
{
    std::size_t len = Length() + _second.Length();
    Buffer<char> str(*(m_str.GetData()), len);
    
    unsigned int j = 0;
    
    for(unsigned int i = Length(); i < len; ++i)
    {
        str[i] = _second.Get_c_Str()[j++];
    }
    
    String ret;
    ret.m_str = str;
    
    return ret;
}

String String::operator+(const char* _second) const
{
    if(_second)
    {
        std::size_t len = Length() + strlen(_second);
        Buffer<char> str(*(m_str.GetData()), len);
        
        unsigned int j = 0;
        
        for(unsigned int i = Length(); i < len; ++i)
        {
            str[i] = _second[j++];
        }
        
        String ret;
        ret.m_str = str;
    
        return ret;
    }
    
    return *this;
}

void String::ToUpper()
{
     for (unsigned int i = 0; i < Length(); ++i)
    {
        m_str[i] = static_cast<char>(toupper(m_str[i]));
    }
}


void String::ToLower()
{
    for (unsigned int i = 0; i < Length(); ++i)
    {
        m_str[i] = static_cast<char>(tolower(m_str[i]));
    }
}


} // namespace advcpp










