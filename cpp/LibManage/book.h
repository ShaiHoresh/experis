#ifndef __BOOK_H__
#define __BOOK_H__

#include <string>


class Book
{
public:
//    Book();
    Book(const string& _ISBN, const string& _title, const string& _author);
    virtual ~Book();
    
    string GetISBN() const;
    string GetTitle() const;
    string GetAuthor() const;
    
private:
    string m_ISBN();
    string m_title();
    string m_Author();
    
    Book(const Book& _book);
    Book& operator=(const Book& _book);

}

#endif /* __BOOK_H__ */









































