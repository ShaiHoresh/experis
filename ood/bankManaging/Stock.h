#ifndef __STOCK_ACCOUNT_H__
#define __STOCK_ACCOUNT_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
#include <string>
#include <iostream>

#include "AccountImpl.h"

class StockAcc: public AccountImpl
{
public:
    StockAcc():AccountImpl(){}
    virtual ~StockAcc(){}
    
    virtual void Update(){std::cout << "Stock account updated" << std::endl;}

private:
    /* data */
};

#endif /* __STOCK_ACCOUNT_H__ */

