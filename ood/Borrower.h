
#ifndef BORROWER_H
#define BORROWER_H

#include <string>
#include <vector>



/**
  * class Borrower
  * 
  */

class Borrower
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Borrower ();

  /**
   * Empty Destructor
   */
  virtual ~Borrower ();

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
  const string& GetName () const
  {
  }


  /**
   * @return const string&
   */
  const string& GetID () const
  {
  }


  /**
   * @return const string&
   */
  const string& GetPhone () const
  {
  }


  /**
   * @return bool
   * @param  isbn
   */
  bool BorrowBook (const string& isbn)
  {
  }


  /**
   * @param  isbn
   */
  void ReturnBook (const string& isbn)
  {
  }


  /**
   */
  void Print () const
  {
  }


  /**
   * @param  name
   * @param  id
   * @param  phoneNo
   */
   Borrower (const string& name, const string& id, const string& phoneNo)
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

  std::string m_id;
  std::string m_name;
  std::string m_phone;
  list<string> m_books;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_id
   * @param new_var the new value of m_id
   */
  void setM_id (std::string new_var)   {
      m_id = new_var;
  }

  /**
   * Get the value of m_id
   * @return the value of m_id
   */
  std::string getM_id ()   {
    return m_id;
  }

  /**
   * Set the value of m_name
   * @param new_var the new value of m_name
   */
  void setM_name (std::string new_var)   {
      m_name = new_var;
  }

  /**
   * Get the value of m_name
   * @return the value of m_name
   */
  std::string getM_name ()   {
    return m_name;
  }

  /**
   * Set the value of m_phone
   * @param new_var the new value of m_phone
   */
  void setM_phone (std::string new_var)   {
      m_phone = new_var;
  }

  /**
   * Get the value of m_phone
   * @return the value of m_phone
   */
  std::string getM_phone ()   {
    return m_phone;
  }

  /**
   * Set the value of m_books
   * @param new_var the new value of m_books
   */
  void setM_books (list<string> new_var)   {
      m_books = new_var;
  }

  /**
   * Get the value of m_books
   * @return the value of m_books
   */
  list<string> getM_books ()   {
    return m_books;
  }
private:



  /**
   * @return const Borrower&
   * @param  bor
   */
  const Borrower& operator_ (const Borrower& bor)
  {
  }

  void initAttributes () ;

};

#endif // BORROWER_H
