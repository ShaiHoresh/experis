#ifndef __MEMPAGE_T_H__
#define __MEMPAGE_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "memManager.h"

 
class MemPage_t: public MemManager_t
{
public:
        // CTORs, DTOR
    MemPage_t();
    MemPage_t(size_t _size);
    virtual ~MemPage_t();
    
    virtual size_t Read(void** _buf, unsigned int _size);
    virtual size_t Read(void** _buf, size_t _pos, unsigned int _size);
    virtual size_t Write(const void* _data, unsigned int _size);
    virtual size_t Write(const void* _data, unsigned int _size ,size_t _pos);
    
    void SetDefaultSize(unsigned int _size);
    bool IsFull() const;
    
private:    // functions
    MemPage_t(const MemPage_t& _page);
    const MemPage_t& operator=(const MemPage_t& _page);

private:    // data
    static size_t m_defCapacity;
    size_t m_curCapacity;
    char* m_data;
};

inline bool MemPage_t::IsFull() const
{
    return m_used == m_curCapacity;
}

inline void MemPage_t::SetDefaultSize(unsigned int _size)
{
    m_defCapacity = _size;
}


#endif /* __MEMPAGE_T_H__ */
