#ifndef __BOOKRECORD_H__
#define __BOOKRECORD_H__

#include <set>

#include "book.h"
#include "person.h"


class BookRecord
{
public:
    BookRecord(Book* _book, unsigned int _noc = 1);
    virtual ~BookRecord();
    
    bool SetNumOfCopies(unsigned int _noc);
    bool IsAvailable() const;
    Person* NextBorrower();
    bool BorrowBook(Person* _per);
    bool ReturnBook(Person* _per);
    
    std::ofstream Report(string _fileName = __TIME__) const;

private:
    /* data */
    Book* m_book;
    unsigned int m_noc;
    std::set<Person*> m_borrowers; //class Person should have operator< !!
    std::queue<Person*> m_waitings;
    
    BookRecord(const BookRecord& br);
    BookRecord& operator=(const BookRecord& br);
    
};
#endif /* __BOOKRECORD_H__ */
