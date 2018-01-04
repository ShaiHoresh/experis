#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <map>
#include "borroweradmin.h"
#include "bookadmin.h"

class Library
{
public:
    Library(const string m_name);
    virtual ~Library();
    
    // should add all functionality of library! 

private:
    string m_name;
    BorrowerAdmin m_borAdmin;
    BookAdmin m_bookAdmin;
    std::multimap<string, Book> m_books;
    
    Library(const Library& _lib);
    Library& operator=(const Library& _lib);
    
};

#endif /* __LIBRARY_H__ */

