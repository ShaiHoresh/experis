#ifndef __BOOKADMIN_H__
#define __BOOKADMIN_H__

#include "bookrecord.h"

class BookAdmin
{
public:
    BookAdmin();
    virtual ~BookAdmin ();
    
    BookRecord& AddBook(const string& _ISBN, const string& _title, const string& _author, unsigned int _noc);
    void RemoveBook(BookRecord& _book);
    
    std::list<BookRecord*> SearchByAuthor(const string& _author) const;
    std::list<BookRecord*> SearchByTitle(const string& _title) const;
    
    bool BorrowBook(const Person& _per, BookRecord& _book);
    bool ReturnBook(const Person& _per, BookRecord& _book);

private:
    /* data */
    std::map<BookRecords*> m_books;
    
    std::multimap<string> m_authors;
    std::multimap<string> m_titles;    
    
    BookAdmin(const BookAdmin& _ba);
    BookAdmin& operator=(const BookAdmin& _ba);
    
};


#endif /* __BOOKADMIN_H__ */
