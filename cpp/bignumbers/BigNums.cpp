#include <climits>
#include <cstring>
#include <cstdio>
#include <algorithm>

#include <iomanip>
#include <locale>
#include <sstream>


#include "BigNums.h"


ostream& operator<<(ostream& os, const BigNumber& _num)
{
    os << _num.Get(_num);
    
    return os;
}

istream& operator>>(istream& is, BigNumber& _num)
{
    string num;
    
    is >> num;
    _num = num;
    
    return is;
}

BigNumber& BigNumber::operator=(const string _num)
{   
    m_num = _num;
    m_length = _num.size();
    
    return *this;
}

BigNumber::BigNumber()
{   
    m_length = 0;
}

BigNumber::BigNumber(const char* _num)
{
    unsigned int i;
    m_length = strlen(_num);
    for(i = 0; i < m_length; ++i)
    {
        if(!isdigit(_num[i]))
        {
            break;
        }
    }
    if(i == m_length)
    {
        m_num = _num;
    }
}

BigNumber::BigNumber(const int _num)
{
    m_num = static_cast<ostringstream*>(&(ostringstream() << _num))->str();
    m_length = m_num.size(); 
}

BigNumber::BigNumber(const BigNumber& _num)
{
    m_length = _num.m_length;
    m_num = _num.m_num;
}

BigNumber::~BigNumber()
{}

BigNumber& BigNumber::operator=(const BigNumber& _num)
{
    if(&_num != this)
    {
        m_num = _num.m_num;
        m_length = _num.m_length;
    }

    return *this;
}

BigNumber& BigNumber::operator=(const int _num)
{
    m_num = static_cast<ostringstream*>( &(ostringstream() << _num) )->str();
    m_length = m_num.size();

    return *this;
}

bool BigNumber::operator==(const BigNumber& _num) const
{
    return !m_num.compare(_num.m_num);
}

bool BigNumber::operator>(const BigNumber& _num) const
{
    if(m_length != _num.m_length)
    {
        return m_length > _num.m_length;
    }

    return (m_num.compare(_num.m_num) > 0);
}

bool BigNumber::operator<(const BigNumber& _num) const
{
    if(m_length != _num.m_length)
    {
        return m_length < _num.m_length;
    }

    return (m_num.compare(_num.m_num) < 0);
}

BigNumber BigNumber::operator+(const BigNumber& _num) const
{
    BigNumber newnum;
    string Short, Long;

    int n1 = m_num.length(), n2 = _num.m_num.length();
 
    if(n1 < n2)
    {
        Short = m_num;
        Long = _num.m_num;
    }
    else
    {
        Long = m_num;
        Short = _num.m_num;
    }
 
    reverse(Short.begin(), Short.end());
    reverse(Long.begin(), Long.end());
    
    int carry = 0;
    for(int i = 0; i < n1; ++i)
    {
        int sum = ((Long[i] - '0') + (Short[i] - '0') + carry);
        newnum.m_num.push_back(sum % 10 + '0');
 
        carry = sum / 10;
    }
 
    for(int i = n1; i < n2; ++i)
    {
        int sum = ((Short[i] - '0') + carry);
        newnum.m_num.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
 
    if(carry)
    {
        newnum.m_num.push_back(carry + '0');
    }
 
    reverse(newnum.m_num.begin(), newnum.m_num.end());

    return newnum;
}

BigNumber BigNumber::operator-(const BigNumber& _num) const
{
    BigNumber newnum;
    string Short, Long;

 
//    if(n1 < n2)
    if(*this > _num)
    {
        Short = m_num;
        Long = _num.m_num;
    }
    else
    {
        Long = m_num;
        Short = _num.m_num;
    }
    int n1 = Short.length(), n2 = Long.length();
 
    reverse(Short.begin(), Short.end());
    reverse(Long.begin(), Long.end());
 
    int carry = 0;
 
    for(int i = 0; i < n1; ++i)
    {
        int sub = ((Short[i] - '0') - (Long[i] - '0') - carry);
        if (sub < 0)
        {
            sub += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
 
        newnum.m_num.push_back(sub + '0');
    }
 
    for(int i = n1; i < n2; ++i)
    {
        int sub = ((m_num[i] - '0') - carry);
        carry = 0;
        newnum.m_num.push_back(sub + '0');
    }
 
    reverse(newnum.m_num.begin(), newnum.m_num.end());
    newnum.m_length = newnum.m_num.size();
    
    return newnum;
}









