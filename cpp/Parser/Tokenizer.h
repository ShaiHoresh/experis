#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <string>
#include <queue>

using namespace std;


class Token
{
public:
    Token(const string& _tokens);
    virtual ~Token();
    
    bool Tokenize(string& _line);
    string& RetreiveNext(string& _str);
    bool IsEmpty();

private:
    string m_tokens;
    queue<string> m_q;
};

#endif /* __TOKENIZER_H__ */

