#include <cctype>
#include <iostream>
#include "Analyzer.h"
using namespace std;

const string types[] = {"int", "char", "float", "short", "long", "double", "void"};
const string key[] = {"if", "else", "for" , "while", "class", "private", "public", "protected", "main", "const", "virtual"};
const string ops[] = {"+", "-", "=", "<", ">", "+", "-", "*", "&", "(", ")", "[", "]", "{", "}", ";"};
	
const set<string> Analyze::m_types(types, types + sizeof(types) / sizeof(types[0]));
const set<string> Analyze::m_keyWords(key, key + sizeof(key) / sizeof(key[0]));
const set<string> Analyze::m_operators(ops, ops + sizeof(ops) / sizeof(ops[0]));

/* Auxiliary function */
void PrintError(const string& _str, size_t m_line)
{
    cout << "error in line " << m_line << ": " << _str << endl;
}
/**********************/

Analyze::Analyze()
{
    InitialMembers();    
}

Analyze::~Analyze()
{
    
}

void Analyze::InitialMembers()
{
    ZeroMembers();
    m_vars.clear();
    m_first = true;
}

void Analyze::ZeroMembers()
{
    m_regBrac = 0;
    m_sqrBrac = 0;
    m_curBrac = 0;
    m_ifElse = 0;
    m_plus = 0;
    m_minus = 0;
    m_ifElse = 0;
    m_type = false;
}

void Analyze::CheckToken(string& _chunk, size_t _line)
{
    m_chunk = _chunk;
    m_line = _line;
    if(m_chunk != "" && m_chunk != " " && m_chunk != "\t" && m_chunk != "\n" && m_chunk != "\r")
    {
        if(m_first)  // look for "main"
        {
            CheckFirst();
        }
        else if(m_types.count(m_chunk))
        {
            TreatTypes();
        }
        else if(m_keyWords.count(m_chunk))
        {
            TreatKeys();
        }
        else if(m_operators.count(m_chunk))
        {
            TreatOperators();
        }
        else if(m_vars.count(m_chunk))
        {
            TreatVars(); //check last != type
        }
        else
        {
            TreatOther();// check validity, and insert if can.
        }
    }
}

void Analyze::CheckFirst()
{
    
    if(m_chunk != "main")
    {
        PrintError("Program must start with \'main\'",m_line);
    }
    m_first = false;
    m_last = m_chunk;
}

void Analyze::TreatTypes()
{
    if(m_types.count(m_last))
    {
        PrintError("double predefined types",m_line);
        m_last = " ";
    }
    else
    {
        m_last = m_chunk;
    }
}

void Analyze::TreatKeys()
{
    if(m_types.count(m_last))
    {
        PrintError("Keyword \'" +m_chunk + "\' can't be an argument",m_line);
    }
    else if(m_chunk == "if")
    {
        m_ifElse++;
    }
    else if(m_chunk == "else")
    {
        if(0 > --m_ifElse)
        {
            PrintError("\'else\' before \'if\'",m_line);
            m_ifElse = 0;
        }
    }
    
    m_last = m_chunk;
}

void Analyze::TreatOperators()
{
    char tok = m_chunk[0];
    
    if(m_types.count(m_last))
    {
        PrintError("\'" + m_chunk + "\' is Invalid argument name",m_line);
    }
    else
    {
        switch(tok)
        {
            case '(':
                m_regBrac++;
            break;
            case ')':
                m_regBrac--;
                if(m_regBrac < 0)
                {
                    PrintError(") before (" , m_line);
                    m_regBrac = 0;
                }
            break;
            case '[':
                m_sqrBrac++;
            break;
            case ']':
                m_sqrBrac--;
                if(m_sqrBrac < 0)
                {
                    PrintError("] before [", m_line);
                    m_sqrBrac = 0;
                }
            break;
            case '{':
                m_curBrac++;
            break;
            case '}':
                m_curBrac--;
                if(m_curBrac < 0)
                {
                    PrintError("} before {" , m_line);
                    m_curBrac = 0;
                }
            break;
            case '+':
                if(3 == ++m_plus)
                {
                    PrintError("+++ is not valid" , m_line);
                    m_plus = 0;
                }
            break;
            case '-':
                if(3 == ++m_minus)
                {
                    PrintError("--- is not valid" , m_line);
                    m_minus = 0;
                }
            break;
            default:
            break;
        }
        
        if(tok != '+') m_plus = 0;
        if(tok != '-') m_minus = 0;
    }
    m_last = m_chunk;
}

void Analyze::TreatVars()
{
    if(m_types.count(m_last))
    {
        PrintError("redefinition of variable \'" + m_chunk + "\'", m_line);
    }
    else
    {
        TreatOther();
    }
    m_last = m_chunk;
}

void Analyze::TreatOther()
{
    if(m_types.count(m_last))
    {
        if(IsValidName())
        {
            m_vars.insert(m_chunk);
        }
        else
        {
            PrintError("\'" + m_chunk + "\' is invalid argument name", m_line);
        }
    }
    else if(!m_vars.count(m_chunk))// && !m_operators.count(m_last))
    {
        PrintError("undeclared variable \'" + m_chunk + "\'", m_line);
    }
    m_last = m_chunk;
}

bool Analyze::IsValidName()
{
    if(isalpha(m_chunk[0]) || m_chunk[0] == '_')
    {
        for (unsigned int i = 1; i < m_chunk.length(); ++i)
        {
            if(!isalnum(m_chunk[i]) && m_chunk[i] != '_')
            {
                return false;
            }
        }
        return true;
    }
    
    return false;
}

void Analyze::PrintBraces()const
{
    if(m_regBrac > 0)
    {
        cout << m_regBrac << " ( are open" << endl;
    }
    if(m_regBrac < 0)
    {
        cout << m_regBrac << " ) are open" << endl;
    }
    if(m_sqrBrac > 0)
    {
        cout << m_sqrBrac << " [ are open" << endl;
    }
    if(m_sqrBrac < 0)
    {
        cout << m_sqrBrac << " ] are open" << endl;
    }
    if(m_curBrac > 0)
    {
        cout << m_curBrac << " { are open" << endl;
    }
    if(m_curBrac < 0)
    {
        cout << m_curBrac << " } are open" << endl;
    }
}












