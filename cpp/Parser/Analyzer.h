#ifndef __ANALYZER_H__
#define __ANALYZER_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <string>
#include <set>
#include <cstddef>
using namespace std;

class Analyze
{
public:
    Analyze();
    virtual ~Analyze();
    
    void CheckToken(string& _chunk, size_t _line);
    
    void InitialMembers();
    void TreatTypes();
    void TreatKeys();
    void TreatOperators();
    void TreatVars();
    void TreatOther();
    void PrintBraces()const;
    
private: // data members
    int m_regBrac;
    int m_sqrBrac;
    int m_curBrac;
    int m_ifElse;
    int m_plus;
    int m_minus;
    bool m_type;
    
    string m_chunk;
    size_t m_line;
    
    set<string> m_vars;
    
    const static set<string> m_types;
    const static set<string> m_keyWords;
    const static set<string> m_operators;
    
    bool m_first;
    string m_last;
    
private: // auxiliary functions
    void CheckFirst();
    bool IsValidName();
    void ZeroMembers();
    
};

#endif /* __ANALYZER_H__ */

