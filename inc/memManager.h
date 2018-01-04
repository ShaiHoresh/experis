#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__

#include <stddef.h>

class MemManager_t
{
public:
    // CTORs & DTOR
    MemManager_t();
    virtual ~MemManager_t();
    
    // functions
    bool IsEmpty() const;
    size_t GetSize() const;
    size_t GetPosition() const;
    bool SetPosition(size_t _pos);
    
    virtual size_t Read(void** _buf, unsigned int _size) = 0;
    virtual size_t Read(void** _buf, size_t _pos, unsigned int _size) = 0;
    virtual size_t Write(const void* _data, unsigned int _size) = 0;
    virtual size_t Write(const void* _data, unsigned int _size ,size_t _pos) = 0;
    
    
    
private:    // functions
    MemManager_t(const MemManager_t& _mem);
    const MemManager_t& operator=(const MemManager_t& _mem);

protected:    // data
    size_t m_position;
    size_t m_used;
};

inline bool MemManager_t::IsEmpty() const
{
    return m_used == 0;
}

inline size_t MemManager_t::GetSize() const
{
    return m_used;
}

inline size_t MemManager_t::GetPosition() const
{
    return m_position;
}
#endif /* __MEMORY_MANAGER_H__ */















