
#ifndef BOOK_H
#define BOOK_H

#include <string>

/**
  * class Book
  * 
  */

class Book
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Book ();

  /**
   * Empty Destructor
   */
  virtual ~Book ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return const string&
   */
  const string& GetISBN () const
  {
  }


  /**
   * @return const string&
   */
  const string& GetTitle () const
  {
  }


  /**
   * @return const string&
   */
  const string& GetAuthor () const
  {
  }


  /**
   * @param  isbn
   * @param  title
   * @param  author
   */
   Book (const string& isbn, const string& title, const string& author)
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

  std::string m_ISBN;
  std::string m_title;
  std::string m_author;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_ISBN
   * @param new_var the new value of m_ISBN
   */
  void setM_ISBN (std::string new_var)   {
      m_ISBN = new_var;
  }

  /**
   * Get the value of m_ISBN
   * @return the value of m_ISBN
   */
  std::string getM_ISBN ()   {
    return m_ISBN;
  }

  /**
   * Set the value of m_title
   * @param new_var the new value of m_title
   */
  void setM_title (std::string new_var)   {
      m_title = new_var;
  }

  /**
   * Get the value of m_title
   * @return the value of m_title
   */
  std::string getM_title ()   {
    return m_title;
  }

  /**
   * Set the value of m_author
   * @param new_var the new value of m_author
   */
  void setM_author (std::string new_var)   {
      m_author = new_var;
  }

  /**
   * Get the value of m_author
   * @return the value of m_author
   */
  std::string getM_author ()   {
    return m_author;
  }
private:



  /**
   * @return Book&
   * @param  book
   */
  Book& operator_ (const Book& book)
  {
  }

  void initAttributes () ;

};

#endif // BOOK_H
