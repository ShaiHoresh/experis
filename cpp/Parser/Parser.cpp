

#include <iostream>
using namespace std;

#include "Parser.h"
#include "Tokenizer.h"
#include "Analyzer.h"

Parser::Parser()
{
    m_token = new Token("(){}[];<>=+-*& \t\n\r");
    m_analyzer = new Analyze;
    m_lineCounter = 0;
}
  
Parser::~Parser()
{
    delete m_token;
    delete m_analyzer;
}
    
void Parser::Parse(const char* _fileName)
{
    if(OpenFile(_fileName))
    {
        while(!m_file.eof())
        {
            ++m_lineCounter;
            CheckNextLine();
        }
        m_analyzer->PrintBraces();
        CloseFile();
        InitialDataMembers();
    }
    else
    {
        cout << "Fatal error: no matching file for: " << _fileName << endl;
    }
}


void Parser::InitialDataMembers()
{
    m_analyzer->InitialMembers();
    m_lineCounter = 0;
}

bool Parser::OpenFile(const char* _fileName)
{
    m_file.open(_fileName);
    
    if(m_file.good())
    {
        return true;
    }
    
    return false;
}
void Parser::CloseFile()
{
    m_file.close();
}

void Parser::CheckNextLine()
{
    getline(m_file, m_curLine);
    string str;
    
    if(m_token->Tokenize(m_curLine))
    {
        while(!m_token->IsEmpty())
        {
            m_token->RetreiveNext(str);
            m_analyzer->CheckToken(str, m_lineCounter);
        }
    }
}












