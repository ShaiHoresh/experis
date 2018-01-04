
#include <cstddef>
#include "Tokenizer.h"

Token::Token(const string& _tokens)
{
    m_tokens = _tokens;
}

Token::~Token()
{}

bool Token::Tokenize(string& _line)
{
    size_t prev = 0;
    size_t cur = _line.find_first_of(m_tokens);
    bool ret;
    
    cur != string::npos ? ret = true : ret = false;
    
    while(cur != string::npos)
    {
        if(string::npos != m_tokens.find(_line[prev]))
        {
            m_q.push(_line.substr(prev, 1));
            ++prev;
            ++cur;
        }
        (_line[cur - 1] == ' ' || _line[cur - 1] == '\r') ? m_q.push(_line.substr(prev, cur - prev - 1)) : m_q.push(_line.substr(prev, cur - prev));
        prev = cur;
        cur = _line.find_first_of(m_tokens, cur + 1);
    }
    
    return ret;
}

string& Token::RetreiveNext(string& _str)
{
    if(!m_q.empty())
    {
        _str = m_q.front();
        m_q.pop();
    }
    
    return _str;
}

bool Token::IsEmpty()
{
    return m_q.empty();
}






