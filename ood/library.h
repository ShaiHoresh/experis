
#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>

/**
  * class Library
  * 
  */

class Library
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Library ();

  /**
   * Empty Destructor
   */
  virtual ~Library ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  bookAd
   * @param  borrowerAd
   */
   Library (BookAdmin* bookAd, BorrowerAdmin* borrowerAd)
  {
  }


  /**
   * @return const vector<Borrower*>*
   * @param  name
   */
  const vector<Borrower*>* FindByName (const string& name) const
  {
  }


  /**
   * @return const Borrower*
   * @param  id
   */
  const Borrower* FindByID (const string& id) const
  {
  }


  /**
   * @return bool
   * @param  isbn
   * @param  name
   * @param  phone
   */
  bool AddBorrower (const string& isbn, const string& name, const string& phone)
  {
  }


  /**
   * @return bool
   * @param  id
   */
  bool RemoveBorrower (const string& id)
  {
  }


  /**
   * @return bool
   * @param  isbn
   * @param  id
   */
  bool BorrowBook (const string& isbn, const string& id)
  {
  }


  /**
   * @return const string&
   * @param  isbn
   * @param  id
   */
  const string& ReturnBook (const string& isbn, const string& id)
  {
  }


  /**
   * @param  id
   */
  void PrintBorrower (const string& id) const
  {
  }


  /**
   * @return bool
   * @param  isbn
   */
  bool IsAvailable (const string& isbn) const
  {
  }


  /**
   * @return bool
   * @param  book
   * @param  numOfCopies
   */
  bool AddBookRecord (const Book* book, unsigned int numOfCopies)
  {
  }


  /**
   * @return bool
   * @param  isbn
   */
  bool RemoveBookRecord (const string& isbn)
  {
  }


  /**
   * @return BookRecord*
   * @param  isbn
   */
  BookRecord* SearchByISBN (const string& isbn) const
  {
  }


  /**
   * @return vector<BookRecord*>*
   * @param  author
   */
  vector<BookRecord*>* SearchByAuthor (const string& author) const
  {
  }


  /**
   * @param  isbn
   */
  void PrintBookRecord (const string& isbn) const
  {
  }


  /**
   * @return vector<BookRecord*>*
   * @param  title
   */
  vector<BookRecord*>* SearchByTitle (const string& title) const
  {
  }


  /**
   * @return const string&
   * @param  isbn
   */
  const string& GetNextInWaitingList (const string& isbn) const
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  BookAdmin* m_bookAdmin;
  BorrowerAdmin* m_borrowerAdmin;
  list<Book*> m_books;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_bookAdmin
   * @param new_var the new value of m_bookAdmin
   */
  void setM_bookAdmin (BookAdmin* new_var)   {
      m_bookAdmin = new_var;
  }

  /**
   * Get the value of m_bookAdmin
   * @return the value of m_bookAdmin
   */
  BookAdmin* getM_bookAdmin ()   {
    return m_bookAdmin;
  }

  /**
   * Set the value of m_borrowerAdmin
   * @param new_var the new value of m_borrowerAdmin
   */
  void setM_borrowerAdmin (BorrowerAdmin* new_var)   {
      m_borrowerAdmin = new_var;
  }

  /**
   * Get the value of m_borrowerAdmin
   * @return the value of m_borrowerAdmin
   */
  BorrowerAdmin* getM_borrowerAdmin ()   {
    return m_borrowerAdmin;
  }

  /**
   * Set the value of m_books
   * @param new_var the new value of m_books
   */
  void setM_books (list<Book*> new_var)   {
      m_books = new_var;
  }

  /**
   * Get the value of m_books
   * @return the value of m_books
   */
  list<Book*> getM_books ()   {
    return m_books;
  }
private:



  /**
   * @param  lib
   */
   Library (const Library& lib)
  {
  }


  /**
   * @return Library&
   * @param  lib
   */
  Library& operator_ (const Library& lib)
  {
  }

  void initAttributes () ;

};

#endif // LIBRARY_H
