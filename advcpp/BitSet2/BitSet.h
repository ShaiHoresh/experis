#ifndef __BITSET_H__
#define __BITSET_H__

#include <cstddef>  // size_t
#include <limits>  // numeric_limits
#include <climits>  // CHAR_BIT
#include <iostream> // operator<<
#include <algorithm>

#include "operators.h"

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

    private:
        T* m_cell;
        std::size_t m_offset;
        
    private:
        Reference();
    };

public:
    explicit BitSet();
    BitSet(const BitSet&);
    BitSet& operator=(const BitSet&);
    BitSet(bool*);   
    ~BitSet();
    
    Reference operator[](std::size_t);
    bool operator[](std::size_t) const;
        
    BitSet& operator^=(const BitSet&);
    BitSet& operator|=(const BitSet&);
    BitSet& operator&=(const BitSet&);
    BitSet operator~();
    void Flip();
    
    BitSet& operator<<=(std::size_t);
    BitSet& operator>>=(std::size_t);
    
    bool operator==(const BitSet&) const;
    bool operator!=(const BitSet&) const;
    
    std::size_t Count() const;
    bool Any() const;
    bool All() const;
    bool None() const;
    
private:
    const static unsigned int NUM_OF_BITS = std::numeric_limits<T>::digits;
    const static unsigned int NUM_OF_CHUNKS = SIZE / NUM_OF_BITS + ((SIZE % NUM_OF_BITS) ? 1 : 0);
    T* m_array;
   
    
private:
    void Set(std::size_t, bool);
    std::size_t ChunkNo(std::size_t) const;
    std::size_t BitNo(std::size_t) const;
    void ClearTail();
};

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator^(const BitSet<SIZE, T>&, const BitSet<SIZE, T>&);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator|(const BitSet<SIZE, T>&, const BitSet<SIZE, T>&);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator&(const BitSet<SIZE, T>&, const BitSet<SIZE, T>&);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator>>(const BitSet<SIZE, T>&, std::size_t);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator<<(const BitSet<SIZE, T>&, std::size_t);

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::Reference::Reference(T* _location, std::size_t _pos)
: m_cell(_location)
, m_offset(_pos)
{}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::Reference::operator bool() const
{
    T ch = 1;
    
    return (*m_cell & (ch <<= m_offset));
}

template <std::size_t SIZE, typename T>
typename BitSet<SIZE, T>::Reference& BitSet<SIZE, T>::Reference::operator=(bool _state)
{
    T mask = _state;
    mask <<= m_offset;
    
    *m_cell == (*m_cell | mask) ? *m_cell &= mask : *m_cell |= mask;
    
    return *this;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet()
{
    m_array = new T[NUM_OF_CHUNKS];
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
inline typename BitSet<SIZE, T>::Reference BitSet<SIZE, T>::operator[](std::size_t _index)
{
    return BitSet<SIZE, T>::Reference(m_array + ChunkNo(_index), BitNo(_index));
}

template<size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet(bool* _arr)
{
	m_array = new T[NUM_OF_CHUNKS];
	std::fill(m_array, m_array + NUM_OF_CHUNKS, 0);

	for(unsigned int i = 0; i < SIZE; ++i)
	{
	    Set(i, _arr[i]);
	}
}

template <std::size_t SIZE, typename T>
void BitSet<SIZE, T>::Set(std::size_t _index, bool _state)
{
    T mask = 1;
    mask <<= BitNo(_index);
    
    _state ? m_array[ChunkNo(_index)] |= mask : m_array[ChunkNo(_index)] &= ~mask;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::operator[](std::size_t _index) const
{
    return m_array[ChunkNo(_index)] & (1 << (BitNo(_index)));
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T> operator^(const BitSet<SIZE, T>& _this, const BitSet<SIZE, T>& _other) 
{
    return BitSet<SIZE, T>(_this) ^= _other;
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T> operator|(const BitSet<SIZE, T>& _this, const BitSet<SIZE, T>& _other) 
{
    return BitSet<SIZE, T>(_this) |= _other;
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T> operator&(const BitSet<SIZE, T>& _this, const BitSet<SIZE, T>& _other) 
{
    return BitSet<SIZE, T>(_this) &= _other;
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T> BitSet<SIZE, T>::operator~()
{
    BitSet<SIZE, T> temp(*this);

    DoOperator(temp.m_array, &temp.m_array[NUM_OF_CHUNKS], m_array, Tilda<T>());
    temp.ClearTail();

    return temp;
}

template <std::size_t SIZE, typename T>
inline void BitSet<SIZE, T>::Flip()
{
    DoOperator(m_array, &m_array[NUM_OF_CHUNKS], m_array, Tilda<T>());
    ClearTail();
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T>& BitSet<SIZE, T>::operator^=(const BitSet& _other) 
{
    DoOperator(m_array, &m_array[NUM_OF_CHUNKS], _other.m_array, Xor<T>());
    
    return *this;
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T>& BitSet<SIZE, T>::operator|=(const BitSet& _other) 
{
    DoOperator(m_array, &m_array[NUM_OF_CHUNKS], _other.m_array, Or<T>());

    return *this;
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T>& BitSet<SIZE, T>::operator&=(const BitSet& _other)
{
    DoOperator(m_array, &m_array[NUM_OF_CHUNKS], _other.m_array, And<T>());

    return *this;
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T> operator<<(const BitSet<SIZE, T>& _this, std::size_t _num)
{
    return BitSet<SIZE, T>(_this) <<= _num;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator<<=(std::size_t _num)
{
    for (std::size_t i = SIZE; i > _num; --i)
    {
        Set(i, (*this)[i - _num]);
    }

    for (std::size_t i = _num; i > 0; --i)
    {
         Set(i - 1, false);
    }
    
    ClearTail();
    
    return *this;
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T> operator>>(const BitSet<SIZE, T>& _this, std::size_t _num)
{
    return BitSet<SIZE, T>(_this) >>= _num;
}


template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator>>=(std::size_t _num)
{
    for (std::size_t i = 0; i < SIZE - _num - 1; ++i)
    {
        Set(i, (*this)[i + _num]);
    }

    for (std::size_t i = SIZE - _num; i < SIZE; ++i)
    {
        Set(i, false);
    }
    
    ClearTail();
    
    return *this;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::operator==(const BitSet& _other) const
{
    return std::equal(m_array, &m_array[NUM_OF_CHUNKS], _other.m_array);
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::operator!=(const BitSet& _other) const
{
    return !(*this == _other);
}

template <std::size_t SIZE, typename T>
std::size_t BitSet<SIZE, T>::Count() const
{
    std::size_t numOfBytes = (SIZE / CHAR_BIT + ((SIZE % CHAR_BIT) ? 1 : 0));
    
    SumBits counter = std::for_each((unsigned char*)m_array, (unsigned char*)(m_array) + numOfBytes, SumBits());

    return counter.counter;
}

template <std::size_t SIZE, typename T>
void BitSet<SIZE, T>::ClearTail()
{
    T mask = ~0;
    mask >>= (NUM_OF_BITS - (SIZE % NUM_OF_BITS));
    m_array[NUM_OF_CHUNKS - 1] &= mask;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::Any() const
{
    return Count();
}
    
template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::All() const
{
    return Count() == SIZE;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::None() const
{
    return !Count();
}

template <std::size_t SIZE, typename T>
std::ostream& operator<<(std::ostream& os, const BitSet<SIZE, T>& bs)
{
    for (unsigned int i = 0; i < 108; ++i)
    {
        std::cout << bs[i];
    }
    return os;
}

}   // namespace advcpp
#endif /* __BITSET_H__ */









