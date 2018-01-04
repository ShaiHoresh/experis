#ifndef __BORROWER_H__
#define __BORROWER_H__

#include <list>

#include "person.h"
#include "bookrecord.h"

class Borrower // :public Person
{
public:
    Borrower();
    Borrower(const string _id, const string _name, const string _phone);
    virtual ~Borrower ();
    
    bool Borrow(BookRecord& _book);
    bool Return(BookRecord& _book);
    
    std::list<BookRecord*>* Report();

private:
    /* data */
    Person* m_person;
    std::list<BookRecord*> m_borrowed;
    
    Borrower(const Borrower& _b);
    Borrower& operator=(const Borrower& _b);
    
};

#endif /* __BORROWER_H__ */

