#ifndef __BIGNUMBERS_H__
#define __BIGNUMBERS_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
 
#include <iostream>
using namespace std;
 

class BigNumber
{
public:
    BigNumber();
    BigNumber(const char* _num);
    BigNumber(const int _num);
    BigNumber(const BigNumber& _num);
    virtual ~BigNumber();
    
    BigNumber& operator=(const BigNumber& _num);
    BigNumber& operator=(const int _num);
    BigNumber operator+(const BigNumber& _num) const;
    BigNumber operator-(const BigNumber& _num) const;
    
    bool operator==(const BigNumber& _num) const;
    bool operator>(const BigNumber& _num) const;
    bool operator<(const BigNumber& _num) const;
    
    const string Get(const BigNumber& _num) const {return m_num;};
    
    friend ostream& operator<<(ostream& os, const BigNumber& _str);
    friend istream& operator>>(istream& os, BigNumber& _str);

private:
    /* data */
    string m_num;
    unsigned int m_length;
    BigNumber& operator=(const string _num);
};


#endif /* __BIGNUMBERS_H__ */

