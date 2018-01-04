#ifndef __BITSET_H__
#define __BITSET_H__

#include <cstddef>  // size_t
#include <limits>  // numeric_limits
#include <iostream>
#include <cstring>


namespace advcpp
{

template <std::size_t SIZE, typename T = unsigned int>
class BitSet
{
    class Reference
    {
    public:
        Reference (T* _array, std::size_t _pos);
/*        ~Reference ();*/
        
        operator bool() const;
        
        Reference& operator=(bool _state);
        Reference& operator=(const Reference&);
        
/*        Reference& Flip();*/
/*        bool operator~()const;*/

    private:
        T* m_cell;
        std::size_t m_offset;
        
    private:
        Reference();
    };

public:
    explicit BitSet();
    BitSet(const BitSet&);
    // TODO add copy assignment operator 
    BitSet& operator=(const BitSet&);
    BitSet(bool*);   
    ~BitSet();
    
    Reference operator[](std::size_t);
    bool operator[](std::size_t) const;
        
    BitSet& operator^=(const BitSet&);
    BitSet& operator|=(const BitSet&);
    BitSet& operator&=(const BitSet&);
    BitSet operator~() const;
    void Flip();
    
    BitSet operator<<(std::size_t) const;
    BitSet& operator<<=(std::size_t);
    BitSet operator>>(std::size_t) const;
    BitSet& operator>>=(std::size_t);
    
    bool operator==(const BitSet&) const;
    bool operator!=(const BitSet&) const;
    
    std::size_t Count() const;
    bool Any() const;
    bool All() const;
    bool None() const;
    
private:
    const static short NUM_OF_BITS = std::numeric_limits<T>::digits;
    const static short NUM_OF_CHUNKS = SIZE / NUM_OF_BITS + ((SIZE % NUM_OF_BITS) ? 1 : 0);
    T* m_array;
    
    
private:
    void Set(std::size_t, bool);
    std::size_t ChunkNo(std::size_t) const;
    std::size_t BitNo(std::size_t) const;
};

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator^(const BitSet<SIZE, T>&, const BitSet<SIZE, T>&);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator|(const BitSet<SIZE, T>&, const BitSet<SIZE, T>&);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator&(const BitSet<SIZE, T>&, const BitSet<SIZE, T>&);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::Reference::Reference(T* _location, std::size_t _pos)
: m_cell(_location)
, m_offset(_pos)
{}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::Reference::operator bool() const
{
    T ch = 1;
    ch <<= m_offset;
    
    return (*m_cell & ch);
}

/*template <std::size_t SIZE, typename T>*/
/*bool BitSet<SIZE, T>::Reference::operator~() const*/
/*{*/
/*    if (bool(this))*/
/*    {*/
/*        */
/*    }*/
/*}*/

template <std::size_t SIZE, typename T>
typename BitSet<SIZE, T>::Reference& BitSet<SIZE, T>::Reference::operator=(bool _state)
{
    T mask = _state;
    mask <<= m_offset;
    
    if (*m_cell == (*m_cell | mask))
    {
        *m_cell &= mask;
    }
    else
    {
        *m_cell |= mask;
    }
    
    return *this;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet()
{
    m_array = new T[SIZE / NUM_OF_BITS + 1];
    std::fill(m_array, m_array + NUM_OF_CHUNKS, 0);
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet(const BitSet& _other)
{
    m_array = new T[NUM_OF_CHUNKS];
    std::copy(_other.m_array, _other.m_array + NUM_OF_CHUNKS, m_array);
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator=(const BitSet& _other)
{
    m_array = new T[NUM_OF_CHUNKS];
    std::copy(_other.m_array, _other.m_array + NUM_OF_CHUNKS, m_array);
    
    return *this;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::~BitSet()
{
    delete[] m_array;
}

template <std::size_t SIZE, typename T>
inline std::size_t BitSet<SIZE, T>::ChunkNo(std::size_t _index) const
{
    return _index / NUM_OF_BITS;
}

template <std::size_t SIZE, typename T>
inline std::size_t BitSet<SIZE, T>::BitNo(std::size_t _index) const
{
    return _index % NUM_OF_BITS;
}

template <std::size_t SIZE, typename T>
typename BitSet<SIZE, T>::Reference BitSet<SIZE, T>::operator[](std::size_t _index)
{
    std::size_t offset = BitNo(_index);
    T* cell = m_array + ChunkNo(_index);
    
    return BitSet<SIZE, T>::Reference(cell, offset);
}

template<size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet(bool* _arr)
{
	m_array = new T[NUM_OF_CHUNKS];
	memset(m_array, 0, NUM_OF_CHUNKS * sizeof(T));
	
	for(unsigned int i = 0; i < SIZE; ++i)
	{
	    Set(i, _arr[i]);
	}
}

template <std::size_t SIZE, typename T>
void BitSet<SIZE, T>::Set(std::size_t _index, bool _state)
{
    //ex
    
    T chunk = m_array[_index / NUM_OF_BITS];
    std::size_t bit = _index % NUM_OF_BITS;
    
    T mask = 1;
    mask <<= bit;
    
    if(_state)
    {
        chunk |= mask;
    }
    else
    {
        mask = ~mask;
        chunk &= mask;
    }
    
    m_array[_index / NUM_OF_BITS] = chunk;
}

template <std::size_t SIZE, typename T>
bool BitSet<SIZE, T>::operator[](std::size_t _index) const
{
    T mask = 1 << (_index % NUM_OF_BITS);
    T cell = m_array[_index / NUM_OF_BITS];
    
    return cell & mask;
}

///////////////////////////////////////////////////////////////////

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator^(const BitSet<SIZE, T>& _this, const BitSet<SIZE, T>& _other) 
{
    BitSet<SIZE, T> ret(_this);

    ret ^= _other;

    return ret;

}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator|(const BitSet<SIZE, T>& _this, const BitSet<SIZE, T>& _other) 
{
/*    BitSet<SIZE, T> ret(*this);*/

/*    for(int i = 0; i < NUM_OF_CHUNKS; ++i)*/
/*    {*/
/*        ret.m_array[i] = (m_array[i] | _other.m_array[i]);*/
/*    }*/
    BitSet<SIZE, T> ret(_this);
    
    ret |= _other;
    
    return ret;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator&(const BitSet<SIZE, T>& _this, const BitSet<SIZE, T>& _other) 
{
    BitSet<SIZE, T> ret(_this);
    
    ret &= _other;
/*    for(int i = 0; i < NUM_OF_CHUNKS; ++i)*/
/*    {*/
/*        ret.m_array[i] = (m_array[i] & _other.m_array[i]);*/
/*    }*/

/*    ret &= _other;*/
    return ret;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> BitSet<SIZE, T>::operator~() const
{
    BitSet<SIZE, T> temp;
    
    for (unsigned int i = 0; i < NUM_OF_CHUNKS; ++i)
    {
        temp.m_array[i] = ~ m_array[i];
    }
    
    return temp;
}

template <std::size_t SIZE, typename T>
void BitSet<SIZE, T>::Flip()
{
    for (unsigned int i = 0; i < NUM_OF_CHUNKS; ++i)
    {
        m_array[i] = ~m_array[i];
    }
}

////////////////////////////////////////////////////////////////////////////

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator^=(const BitSet& _other) 
{
    for (unsigned int i = 0; i < NUM_OF_CHUNKS; ++i)
    {
        m_array[i] ^= _other.m_array[i];
    }

    return *this;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator|=(const BitSet& _other) 
{
    for (unsigned int i = 0; i < NUM_OF_CHUNKS; ++i)
    {
        m_array[i] |= _other.m_array[i];
    }

    return *this;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator&=(const BitSet& _other)
{
    for (unsigned int i = 0; i < NUM_OF_CHUNKS; ++i)
    {
        m_array[i] &= _other.m_array[i];
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////
template <std::size_t SIZE, typename T>
BitSet<SIZE, T> BitSet<SIZE, T>::operator<<(std::size_t _num) const
{
    BitSet<SIZE, T> ret;
    
    for (unsigned int i = 0; i < SIZE - _num; ++i)
    {
        ret[i + _num] = (*this)[i];
    }
    
    return ret;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator<<=(std::size_t _num)
{
    if(_num)
    {
        for (std::size_t i = SIZE; i > _num; --i)
        {
            Set(i, (*this)[i - _num]);
        }

        for (std::size_t i = _num; i > 0; --i)
        {
             Set(i - 1, false);
        }
    }
/*    if(_num)*/
/*    {*/
/*        Set(0, false);*/
/*    }*/
    
    return *this;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> BitSet<SIZE, T>::operator>>(std::size_t _num) const
{
    BitSet<SIZE, T> ret;
    
    for (std::size_t i = 0; i < SIZE - _num; ++i)
    {
        ret[i] = (*this)[i + _num];
    }
    
    return ret;
}


template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator>>=(std::size_t _num)
{
/*    BitSet<SIZE, T> temp;*/
    
    for (std::size_t i = 0; i < SIZE - _num - 1; ++i)
    {
        Set(i, (*this)[i + _num]);
    }

    for (std::size_t i = SIZE - _num; i < SIZE; ++i)
    {
         Set(i, false);
    }
    
    return *this;
}
/////////////////////////////////////////////////////////////////////

template <std::size_t SIZE, typename T>
bool BitSet<SIZE, T>::operator==(const BitSet& _other) const
{
    for(unsigned int i = 0; i < NUM_OF_CHUNKS - 1; ++i)
    {
        if(m_array[i] != _other.m_array[i])
        {
            return false;
        }
    }
    
    for(unsigned int i = NUM_OF_BITS * (NUM_OF_CHUNKS - 1); i < SIZE; ++i)
    {
        if((*this)[i] != _other[i])
        {
            return false;
        }
    }
    
    return true;
}

template <std::size_t SIZE, typename T>
bool BitSet<SIZE, T>::operator!=(const BitSet& _other) const
{
    return !(*this == _other);
}
/////////////////////////////////////////////////////////////////////

template <std::size_t SIZE, typename T>
std::size_t BitSet<SIZE, T>::Count() const
{
    std::size_t counter = 0;
    
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        if((*this)[i])
        {
            ++counter;
        }
    }
    
    return counter;
}

template <std::size_t SIZE, typename T>
bool BitSet<SIZE, T>::Any() const
{
    for(unsigned int i = 0; i < NUM_OF_CHUNKS - 1; ++i)
    {
        if(m_array[i] > 0)
        {
            return true;
        }
    }
    
    for(unsigned int i = NUM_OF_BITS * (NUM_OF_CHUNKS - 1); i < SIZE; ++i)
    {
        if((*this)[i])
        {
            return true;
        }
    }
    
    return false;
}
    
template <std::size_t SIZE, typename T>
bool BitSet<SIZE, T>::All() const
{
    for(unsigned int i = 0; i < NUM_OF_CHUNKS - 1; ++i)
    {
        if(m_array[i] == 0)
        {
            return false;
        }
    }
    
    for(unsigned int i = NUM_OF_BITS * (NUM_OF_CHUNKS - 1); i < SIZE; ++i)
    {
        if(!(*this)[i])
        {
            return false;
        }
    }
    
    return true;
}

template <std::size_t SIZE, typename T>
bool BitSet<SIZE, T>::None() const
{
    return !Any();
}


template <std::size_t SIZE, typename T>
std::ostream& operator<<(std::ostream& os, const BitSet<SIZE, T>& bs)
{
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << bs[i];
    }
    return os;
}

}   // namespace advcpp
#endif /* __BITSET_H__ */









