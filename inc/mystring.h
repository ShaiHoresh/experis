#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <stddef.h>
#include <iostream>
#include "buffer.h"

using namespace std;

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
class String_t:public Buffer
{
    public:
        //String_t();       // CTOR
        ~String_t();      // DTOR
        String_t(const char* _src = 0);   // CTOR from ...
        String_t(const String_t& _src);     // copy CTOR
        const String_t& operator=(const String_t& _str);  // Assignment operator
        // mem-functions        
        size_t          Length() const;
//        int             Set(const char* _new);
//        const char*     Get() const;
        int             Compare(const String_t& _cmp) const;
        void            Print() const;
        void            Upper();
        void            Lower();
        void            Prepend(const char* _pre);
        void            Prepend(const String_t& _pre);
        bool            Contains(const char* _sub) const;
        int             FirstOccurrence(const char _c) const;
        int             LastOccurrence(const char _c) const;
        
        // static
        static size_t   SetClassCapacity(size_t _newCap)
                        {
                            int temp = classCapacity;
                            while(_newCap > classCapacity)
                            {
                                classCapacity *= 2;
                            }
                            
                            return temp;
                        }
        
        static size_t   GetClassCapacity()
                        {
                            return classCapacity;
                        }
        
        static void     SetCaseSens(bool _value)
                        {
                            caseSens = _value;
                        }
        
        static bool     GetCaseSens()
                        {
                            return caseSens;
                        }

        // operators
        const String_t& operator+=(const String_t& _str);
        bool operator<(const String_t& _str);
        bool operator>(const String_t& _str);
        bool operator>=(const String_t& _str);
        bool operator<=(const String_t& _str);
        bool operator==(const String_t& _str);
        bool operator!=(const String_t& _str);
        const char operator[](size_t _index) const;
        String_t operator()(int _start, unsigned int _len);

    private:
        // data 
        char*           str;
        size_t          length;
        size_t          myCapacity;
        static size_t   classCapacity;
        static bool     caseSens;
        static size_t   numOfStrings;
        
    private:
        // auxiliary func
        void    CreateFrom(const char* _str);
        void    CreateFromN(const char* _str, unsigned int _len);
        String_t(const char* _src, unsigned int _len);
        
};

ostream& operator << (ostream& os, const String_t& _str);
istream& operator >> (istream& os, String_t& _str);
/*
inline size_t String_t::Length() const
{
    return length;
}

inline const char* String_t::Get() const
{
    return str;
}
*/
inline void String_t::Print() const
{
    cout << str << endl;
}

#endif /* __MYSTRING_H__ */

