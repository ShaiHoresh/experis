#ifndef __ASCIIIO_T_H__
#define __ASCIIIO_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <stdio.h>
#include <string.h>

#include "virtIO_t.h"


using namespace std;

class asciiIO_t: public virtIO_t
{

public:
    asciiIO_t();
    asciiIO_t(const char* _pathName, const char* _mode);
    ~asciiIO_t();
    
    virtual void CheckWrite();
    virtual void CheckRead();
    
    virtual asciiIO_t& operator<<(int _i){return Write(_i, "%d");}
    virtual asciiIO_t& operator<<(char _i){return Write(_i, "%c");}
    virtual asciiIO_t& operator<<(short _i){return Write(_i, "%d");}
    virtual asciiIO_t& operator<<(long _i){return Write(_i, "%ld");}
    virtual asciiIO_t& operator<<(float _i){return Write(_i, "%f");}
    virtual asciiIO_t& operator<<(double _i){return Write(_i, "%f");}
    virtual asciiIO_t& operator<<(unsigned int _i){return Write(_i, "%d");}
    virtual asciiIO_t& operator<<(unsigned char _i){return Write(_i, "%c");}
    virtual asciiIO_t& operator<<(unsigned short _i){return Write(_i, "%hu");}
    virtual asciiIO_t& operator<<(unsigned long _i){return Write(_i, "%lu");}
    
    virtual asciiIO_t& operator>>(int& _i){return Read(_i, "%d");}
    virtual asciiIO_t& operator>>(char& _i){return Read(_i, "%c");}
    virtual asciiIO_t& operator>>(short& _i){return Read(_i, "%d");}
    virtual asciiIO_t& operator>>(long& _i){return Read(_i, "%ld");}
    virtual asciiIO_t& operator>>(float& _i){return Read(_i, "%f");}
    virtual asciiIO_t& operator>>(double& _i){return Read(_i, "%f");}
    virtual asciiIO_t& operator>>(unsigned int& _i){return Read(_i, "%d");}
    virtual asciiIO_t& operator>>(unsigned char& _i){return Read(_i, "%c");}
    virtual asciiIO_t& operator>>(unsigned short& _i){return Read(_i, "%hu");}
    virtual asciiIO_t& operator>>(unsigned long& _i){return Read(_i, "%lu");}
    
    template <class T>
    asciiIO_t& Write(T _t, const char* _format)
    {
        CheckWrite();
        (m_rw == 0 || m_rw == 2) ? fprintf(m_file, _format, _t) : throw(WRITE_ERR);
        m_status = OK_E;
       
        return *this;
    }

    template <class T>
    asciiIO_t& Read(T& _t, const char* _format)
    {
        CheckRead();
        (m_rw == 1 || m_rw == 2) ? fscanf(m_file, _format, &_t) : throw(READ_ERR);
        m_status = OK_E;
        
        return *this;
    }

private:
    asciiIO_t(const asciiIO_t& _io);
    asciiIO_t& operator=(const asciiIO_t& _io);
    
};

asciiIO_t::asciiIO_t()
{}

asciiIO_t::asciiIO_t(const char* _pathName, const char* _mode): virtIO_t(_pathName, _mode)
{}

asciiIO_t::~asciiIO_t()
{}

void asciiIO_t::CheckWrite()
{
    if(strcmp(m_mode, "w") == 0 || strcmp(m_mode, "a") == 0 || strcmp(m_mode, "w+") == 0 || strcmp(m_mode, "a+") == 0)
    {
        m_rw = 0;
    }
}

void asciiIO_t::CheckRead()
{
    if(strcmp(m_mode, "r") == 0 || strcmp(m_mode, "a") == 0 || strcmp(m_mode, "r+") == 0 || strcmp(m_mode, "a+") == 0)
    {
        m_rw = 1;
    }
}


#endif /* __ASCIIIO_T_H__ */
