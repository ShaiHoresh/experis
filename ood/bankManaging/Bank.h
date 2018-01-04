#ifndef __BANK_H__
#define __BANK_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "Subject.h"

class Bank: public Subject
{
public:
    virtual ~Bank();

    static Bank& CreateBank() {return m_bank;}
    
    void Destroy();
    bool OpenAccount(const std::string& _type);
    
    virtual void Notify(const std::string& _whoAmI);
    void GiveBonus();
    void Invest();
    void Meeting();

private:
    static Bank m_bank;
    
private:
    Bank(){}
    Bank(const Bank&);
    void operator=(Bank&);
};

#endif /* __BANK_H__ */

