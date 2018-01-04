#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stddef.h>
#include <iostream>
using namespace std;

/** 
 * @brief class Buffer taking care of managing the buffer needs...
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

class Buffer
{
public:
    // constractors assignment operator and destractor
    //Buffer();
    ~Buffer();
    Buffer(const char* _array = 0);
    Buffer(const size_t _size);
    Buffer(const char* _array, size_t _size);
    Buffer(const Buffer& _buf);
    const Buffer& operator=(const Buffer& _buf);
    
    // mem functions
    int             Set(const char* _new);
    const char*     Get() const;
    size_t          GetSize() const;
    const char*     ReSize(const size_t _newSize);
    
    // static functions
    static size_t   SetDefCapacity(size_t _newCap)
                    {
                        size_t temp = defCapacity;
                        while(_newCap > defCapacity)
                        {
                            defCapacity *= 2;
                        }
                        
                        return temp;
                    }
    
    // operators
    char& operator[](const size_t _index);
    const char& operator[](const size_t _index) const;
    
protected:
    // data
    char*           buffer;
    size_t          size;
    
private:
    // data
    size_t          myCapacity;
    static size_t   defCapacity;
    
private:
    // auxiliary functions
    char* CreateFrom(const char* _str, const size_t _size = 0);
};

ostream& operator << (ostream& os, const Buffer& _str);
istream& operator >> (istream& os, Buffer& _str);

inline size_t Buffer::GetSize() const
{
    return size;
}

inline const char* Buffer::Get() const
{
    return buffer;
}

#endif /* __BUFFER_H__ */

