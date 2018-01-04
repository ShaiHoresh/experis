#include <string.h>
#include <cctype>
#include <stdexcept>

#include "String.h"
namespace advcpp
{

String::String()
{
    m_str = new Buffer<char>();
}

String::String(const char* _data)
{
    std::size_t len = strlen(_data);
    m_str = new Buffer<char>(*_data, len);
}

String::String(const String&_other)
{
    m_str = new Buffer<char>(*(_other.m_str));
}

String::~String()
{
    delete m_str;
}

String& String::operator=(const String& _other) 
{
    if(this != &_other)
    {
        *m_str = *(_other.m_str);
    }
    
    return *this;
}

bool String::operator==(const String& _other) const
{
    return !strcmp(m_str->GetData(), _other.m_str->GetData());
}

bool String::operator!=(const String& _other) const
{
    return strcmp(m_str->GetData(), _other.m_str->GetData());
}

const char String::operator[](std::size_t _index) const
{
    if(Length() < _index)
    {
        return 7;       //TODO throw exception
    }
    return (m_str->GetData())[_index];
}

char String::operator[](std::size_t _index)
{
    if(Length() < _index)
    {
        return 7;       //TODO throw exception
    }
    return (m_str->GetData())[_index];
}


//String String::operator+(const String&) const
//{
//    std::size_t len = strlen(_data);
//    m_str = new Buffer<char>(_data, len);
//    
//    String temp;
//    temp.m_str =
//}

void String::ToUpper()
{
    for (unsigned int i = 0; i < Length(); ++i)
    {
        toupper((m_str->GetData())[i]);
    }
}


void String::ToLower()
{
    for (unsigned int i = 0; i < Length(); ++i)
    {
        tolower((m_str->GetData())[i]);
    }
}


} // namespace advcpp










