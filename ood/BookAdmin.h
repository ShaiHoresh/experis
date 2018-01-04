
#ifndef BOOKADMIN_H
#define BOOKADMIN_H

#include <string>
#include <vector>



/**
  * class BookAdmin
  * 
  */

class BookAdmin
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  BookAdmin ();

  /**
   * Empty Destructor
   */
  virtual ~BookAdmin ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



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
  bool RemoveRecord (const string& isbn)
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
   * @return vector<BookkRecord*>*
   * @param  title
   */
  vector<BookkRecord*>* SearchByTitle (const string& title)
  {
  }


  /**
   * @return bool
   * @param  isbn
   * @param  id
   */
  bool ReturnBook (const string& isbn, const string& id)
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
   * @return unsigned int
   * @param  isbn
   */
  unsigned int GetNumOfCopies (const string& isbn) const
  {
  }


  /**
   * @return unsigned int
   * @param  isbn
   */
  unsigned int GetAvailableCopies (const string& isbn) const
  {
  }


  /**
   * @return const string&
   * @param  isbn
   */
  const string& GetNextInWaitingList (const string& isbn) const
  {
  }


  /**
   * @param  isbn
   */
  void PrintRecord (const string& isbn)
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

  map<BookRecord*> m_bookRecords;
  multimap<string, BookRecord*> m_authors;
  multimap<string, BookRecord*> m_titles;
  vector<string> m_searchResult;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_bookRecords
   * @param new_var the new value of m_bookRecords
   */
  void setM_bookRecords (map<BookRecord*> new_var)   {
      m_bookRecords = new_var;
  }

  /**
   * Get the value of m_bookRecords
   * @return the value of m_bookRecords
   */
  map<BookRecord*> getM_bookRecords ()   {
    return m_bookRecords;
  }

  /**
   * Set the value of m_authors
   * @param new_var the new value of m_authors
   */
  void setM_authors (multimap<string, BookRecord*> new_var)   {
      m_authors = new_var;
  }

  /**
   * Get the value of m_authors
   * @return the value of m_authors
   */
  multimap<string, BookRecord*> getM_authors ()   {
    return m_authors;
  }

  /**
   * Set the value of m_titles
   * @param new_var the new value of m_titles
   */
  void setM_titles (multimap<string, BookRecord*> new_var)   {
      m_titles = new_var;
  }

  /**
   * Get the value of m_titles
   * @return the value of m_titles
   */
  multimap<string, BookRecord*> getM_titles ()   {
    return m_titles;
  }

  /**
   * Set the value of m_searchResult
   * @param new_var the new value of m_searchResult
   */
  void setM_searchResult (vector<string> new_var)   {
      m_searchResult = new_var;
  }

  /**
   * Get the value of m_searchResult
   * @return the value of m_searchResult
   */
  vector<string> getM_searchResult ()   {
    return m_searchResult;
  }
private:



  /**
   * @param  bookAd
   */
   BookAdmin (const BookAdmin& bookAd)
  {
  }


  /**
   * @return const BookAdmin&
   * @param  bookAd
   */
  const BookAdmin& operator_ (const BookAdmin& bookAd)
  {
  }

  void initAttributes () ;

};

#endif // BOOKADMIN_H
