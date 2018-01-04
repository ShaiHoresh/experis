#ifndef __OPERATORS_H__
#define __OPERATORS_H__

template<typename T>
struct Or
{
    T operator()(T r, T l)
    {
        return r | l;
    }
};

template<typename T>
struct And
{
    T operator()(T r, T l)
    {
        return r & l;
    }
};

template<typename T>
struct Xor
{
    T operator()(T r, T l)
    {
        return r ^ l;
    }
};

template<typename T>
struct Tilda
{
    T operator()(T r, T l)
    {
        return ~r;
    }
};

template<class T, class Operator>
void DoOperator(T* destBegin, T* destEnd, T* sourceBegin, Operator op)
{
    std::transform(destBegin, destEnd, sourceBegin, destBegin, op);
}

struct SumBits
{
    SumBits():counter(0){}
    std::size_t operator()(unsigned char x) 
    {
        x = static_cast<unsigned char>((x & 0x55) + ((x >> 1) & 0x55));
        x = static_cast<unsigned char>((x & 0x33) + ((x >> 2) & 0x33));
        counter += (x & 0x0f) + ((x >> 4) & 0x0f);
        return counter;
    }
    std::size_t counter;
};

#endif /* __OPERATORS_H__ */

