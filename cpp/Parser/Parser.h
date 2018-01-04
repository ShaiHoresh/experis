#ifndef __PARSER_H__
#define __PARSER_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
#include <fstream>
#include <string>

using namespace std;

class Token;
class Analyze;

class Parser
{
public:
    Parser();
    virtual ~Parser();
    
    void Parse(const char* _fileName);
    
    
private:
    /* data */
    ifstream m_file;
    string m_fileName;
    string m_curLine;
    size_t m_lineCounter; //?
    
    Analyze* m_analyzer;
    Token* m_token;

private:
    void InitialDataMembers();
    bool OpenFile(const char* _fileName);
    void CloseFile();
    void CheckNextLine();
};

#endif /* __PARSER_H__ */

