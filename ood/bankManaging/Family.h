#ifndef __FAMILY_ACCOUNT_H__
#define __FAMILY_ACCOUNT_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <string>
#include <iostream>
#include "AccountImpl.h"
#include "Subject.h"


class FamilyAcc: public AccountImpl
{
friend class AccountFactory;
public:
    FamilyAcc():AccountImpl(){}
    virtual ~FamilyAcc(){}
    
    virtual void Update(){std::cout << "Family account updated" << std::endl;}

private:
    /* data */
};

#endif /* __FAMILY_ACCOUNT_H__ */

