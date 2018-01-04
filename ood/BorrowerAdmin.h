
#ifndef BORROWERADMIN_H
#define BORROWERADMIN_H

#include <string>
#include <vector>



/**
  * class BorrowerAdmin
  * 
  */

class BorrowerAdmin
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  BorrowerAdmin ();

  /**
   * Empty Destructor
   */
  virtual ~BorrowerAdmin ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return vector<Borrower*>*
   * @param  name
   */
  vector<Borrower*>* SearchByName (const string& name) const
  {
  }


  /**
   * @return Borrower*
   * @param  id
   */
  Borrower* SearchByID (const string& id) const
  {
  }


  /**
   * @return bool
   * @param  borrower
   */
  bool AddBorrower (Borrower* borrower)
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
   * @param  id
   */
  bool BorrowBook (const string& id)
  {
  }


  /**
   * @return bool
   * @param  id
   */
  bool ReturnBook (const string& id)
  {
  }


  /**
   */
  void PrintBorrower () const
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

  multimap<string, Borrower*> m_borrowerNames;
  map<string, Borrower*> m_borrowers;
  vector<Borrower*> m_searchResult;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_borrowerNames
   * @param new_var the new value of m_borrowerNames
   */
  void setM_borrowerNames (multimap<string, Borrower*> new_var)   {
      m_borrowerNames = new_var;
  }

  /**
   * Get the value of m_borrowerNames
   * @return the value of m_borrowerNames
   */
  multimap<string, Borrower*> getM_borrowerNames ()   {
    return m_borrowerNames;
  }

  /**
   * Set the value of m_borrowers
   * @param new_var the new value of m_borrowers
   */
  void setM_borrowers (map<string, Borrower*> new_var)   {
      m_borrowers = new_var;
  }

  /**
   * Get the value of m_borrowers
   * @return the value of m_borrowers
   */
  map<string, Borrower*> getM_borrowers ()   {
    return m_borrowers;
  }

  /**
   * Set the value of m_searchResult
   * @param new_var the new value of m_searchResult
   */
  void setM_searchResult (vector<Borrower*> new_var)   {
      m_searchResult = new_var;
  }

  /**
   * Get the value of m_searchResult
   * @return the value of m_searchResult
   */
  vector<Borrower*> getM_searchResult ()   {
    return m_searchResult;
  }
private:



  /**
   * @param  BorrowerAd
   */
   BorrowerAdmin (const BorrowerAdmin& BorrowerAd)
  {
  }


  /**
   * @return BorrowerAdmin&
   * @param  borAd
   */
  BorrowerAdmin& operator_ (const BorrowerAdmin& borAd)
  {
  }

  void initAttributes () ;

};

#endif // BORROWERADMIN_H
