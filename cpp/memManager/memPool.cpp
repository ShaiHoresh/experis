#include <memPool.h>


void MemPool_t::AddPage()
{
    MemPage_t* page = new MemPage_t();
    if(!page)
    {
        // TODO something
    }
    m_vec.push_back(page);
}

MemPool_t::MemPool_t()
{
    AddPage();
}

MemPool_t::~MemPool_t()
{
    for(size_t i = 0; i < m_vec.size(); ++i)
    {
        delete m_vec[i];
    }
}

size_t MemPool_t::FindPage(size_t _position, size_t* _offset)
{
    size_t sum = 0, i = 0, nop = m_vec.size();
    
    while(sum < _position && i < nop)
    {
        sum += m_vec[i]->GetSize();
        ++i;
    }
    
    *_offset = sum - _position;
    
    return i;
}

size_t MemPool_t::Read(void** _buf, unsigned int _size) 
{
    return Read(_buf, GetPosition(), _size);
}

size_t MemPool_t::Read(void** _buf, size_t _pos, unsigned int _size)
{
    if(!_buf || _pos > GetSize())
    {
        return 0;
    }
    
    size_t offset = 0, page = FindPage(_pos, &offset);
    m_position = _pos;
    size_t readed = m_vec[page]->Read(_buf, offset, _size);
    size_t vecSize = m_vec.size();
    while(readed < _size || page == vecSize)
    {
        m_position += readed;
        _size -= (unsigned int)readed;
/*        ++page;           It does not work!!! */
        readed = m_vec[page]->Read(_buf + m_position, 0, _size);
    }
    
    return readed;
}

size_t MemPool_t::Write(const void* _data, unsigned int _size)
{
    return Write(_data, _size, GetPosition());
}

size_t MemPool_t::Write(const void* _data, unsigned int _size ,size_t _pos)
{
    if (!_data || _pos > GetSize())
    {
        return 0;        
    }
    
    size_t offset = 0;
    size_t page = FindPage(_pos, &offset);
    unsigned int written = 0;
    
    written = (unsigned int)m_vec[page]->Write(_data, _size, offset);

    while(written < _size)
    {
        _size -= written;
        AddPage();
        ++page;
        written = (unsigned int)m_vec[page]->Write(_data, _size, 0);
    }
    
    return 1;
}
    
    
    
    
   
    
    
    
    
    
    
    
