#ifndef __BORROWERADMIN_H__
#define __BORROWERADMIN_H__

#include <string>
#include <map>
#include <fstream>

#include "borrower.h"

class BorrowerAdmin
{
public:
    BorrowerAdmin();
    virtual ~BorrowerAdmin ();
    
    Borrower& Add(const string _id, const string _name, const string _phone);
    void Remove(Person* _per);
    Borrower& SearchID(const string _id) const;
    Borrower& SearchName(const string _name) const;
    
    std::ofstream Report() const;

private:
    std::multimap<string, Borrower> m_borrowersIDs; //map *sorted* by IDs
    std::multimap<string, Borrower> m_borrowersNames; //map *sorted* by Names
    
    BorrowerAdmin(const BorrowerAdmin& _ba);
    BorrowerAdmin& operator=(const BorrowerAdmin& _ba);
        
};

#endif /* __BORROWERADMIN_H__ */

