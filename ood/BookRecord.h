
#ifndef BOOKRECORD_H
#define BOOKRECORD_H

#include <string>
#include <vector>



/**
  * class BookRecord
  * 
  */

class BookRecord
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  BookRecord ();

  /**
   * Empty Destructor
   */
  virtual ~BookRecord ();

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
   * @param  id
   */
  bool ReturnBook (const string& id)
  {
  }


  /**
   * @return bool
   * @param  id
   */
  bool BorrowBook (const string& id)
  {
  }


  /**
   * @return unsigned int
   */
  unsigned int GetNumOfCopies () const
  {
  }


  /**
   * @return unsigned int
   */
  unsigned int GetNumOfAvailbleCopies () const
  {
  }


  /**
   * @return unsigned int
   * @param  id
   */
  unsigned int AddToWaitingList (const string& id)
  {
  }


  /**
   * @return const string&
   */
  const string& GetNextInWaitingList () const
  {
  }


  /**
   */
  void Print () const
  {
  }


  /**
   */
  void PrintWaitingList () const
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

  Book* m_book;
  unsigned int m_numOfCopies;
  unsigned int m_availableCopies;
  list<string> m_borrowers;
  queue<string> m_waitingList;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_book
   * @param new_var the new value of m_book
   */
  void setM_book (Book* new_var)   {
      m_book = new_var;
  }

  /**
   * Get the value of m_book
   * @return the value of m_book
   */
  Book* getM_book ()   {
    return m_book;
  }

  /**
   * Set the value of m_numOfCopies
   * @param new_var the new value of m_numOfCopies
   */
  void setM_numOfCopies (unsigned int new_var)   {
      m_numOfCopies = new_var;
  }

  /**
   * Get the value of m_numOfCopies
   * @return the value of m_numOfCopies
   */
  unsigned int getM_numOfCopies ()   {
    return m_numOfCopies;
  }

  /**
   * Set the value of m_availableCopies
   * @param new_var the new value of m_availableCopies
   */
  void setM_availableCopies (unsigned int new_var)   {
      m_availableCopies = new_var;
  }

  /**
   * Get the value of m_availableCopies
   * @return the value of m_availableCopies
   */
  unsigned int getM_availableCopies ()   {
    return m_availableCopies;
  }

  /**
   * Set the value of m_borrowers
   * @param new_var the new value of m_borrowers
   */
  void setM_borrowers (list<string> new_var)   {
      m_borrowers = new_var;
  }

  /**
   * Get the value of m_borrowers
   * @return the value of m_borrowers
   */
  list<string> getM_borrowers ()   {
    return m_borrowers;
  }

  /**
   * Set the value of m_waitingList
   * @param new_var the new value of m_waitingList
   */
  void setM_waitingList (queue<string> new_var)   {
      m_waitingList = new_var;
  }

  /**
   * Get the value of m_waitingList
   * @return the value of m_waitingList
   */
  queue<string> getM_waitingList ()   {
    return m_waitingList;
  }
private:



  /**
   * @return BookRecord&
   * @param  bookrcd
   */
  BookRecord& operator_ (const BookRecord& bookrcd)
  {
  }


  /**
   * @param  bookrcd
   */
   BookRecord (const BookRecord& bookrcd)
  {
  }

  void initAttributes () ;

};

#endif // BOOKRECORD_H
