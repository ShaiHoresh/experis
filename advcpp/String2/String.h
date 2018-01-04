#ifndef __String_H__
#define __String_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <cstddef>
#include "Buffer.h"

namespace advcpp
{
class String
{
public:
    explicit String();
    explicit String(const char*);
    String(const String&);
    virtual ~String();
    
    String& operator=(const String&);
    
    bool operator==(const String&) const;
    bool operator!=(const String&) const;
    const char operator[](std::size_t) const;
    char operator[](std::size_t);
    String& operator+(const String&) const;
    
    inline char* Get_c_Str() const;
    
    void ToUpper();
    void ToLower();
    
    inline std::size_t Length() const;

private:
    Buffer<char>* m_str;
};

char* String::Get_c_Str() const
{
    return m_str->GetData();
}

std::size_t String::Length() const
{
    return m_str->GetSize();
}

} // namespace advcpp
#endif /* __String_H__ */


