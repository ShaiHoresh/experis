#ifndef __BINIO_T_H__
#define __BINIO_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <stdio.h>
#include <string.h>

#include "virtIO_t.h"


class virtIO_t;

using namespace std;

class binIO_t: public virtIO_t
{

public:
    binIO_t();
    binIO_t(const char* _pathName, const char* _mode);
    ~binIO_t();
    
    virtual void CheckWrite();
    virtual void CheckRead();
    
    virtual binIO_t& operator<<(int _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(char _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(short _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(long _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(float _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(double _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(unsigned int _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(unsigned char _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(unsigned short _i){ return Write(_i) ;}
    virtual binIO_t& operator<<(unsigned long _i){ return Write(_i) ;}
    
    virtual binIO_t& operator>>(int& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(char& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(short& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(long& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(float& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(double& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(unsigned int& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(unsigned char& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(unsigned short& _i){ return Read(_i) ;}
    virtual binIO_t& operator>>(unsigned long& _i){ return Read(_i) ;}
    
    binIO_t& operator>>(void* _buf);
    binIO_t& operator<<(const void* _buf);
    
    void operator,(int len);
    
    template <class T>
    binIO_t& Write(T& _t, int size = sizeof(T))
    {
        CheckWrite();
        m_rw == 0 ? fwrite(&_t, size, 1, m_file) : throw(WRITE_ERR);
        m_status = OK_E;
       
        return *this;
    }

    template <class T>
    binIO_t& Read(T& _t, int size = sizeof(T))
    {
        CheckRead();
        m_rw == 1 ? fread(&_t, size, 1, m_file) : throw(READ_ERR);
        m_status = OK_E;
        
        return *this;
    }
private:
    binIO_t(const binIO_t& _io);
    binIO_t& operator=(const binIO_t& _io);
    
    void* m_loc;
    
};

binIO_t::binIO_t()
{}

binIO_t::binIO_t(const char* _pathName, const char* _mode): virtIO_t(_pathName, _mode)
{}

binIO_t::~binIO_t()
{}

void binIO_t::CheckWrite()
{
    if(strcmp(m_mode, "wb") == 0 || strcmp(m_mode, "ab") == 0 || strcmp(m_mode, "wb+") == 0 || strcmp(m_mode, "ab+") == 0)
    {
        m_rw = 0;
    }
}
void binIO_t::CheckRead()
{
    if(strcmp(m_mode, "rb") == 0 || strcmp(m_mode, "ab") == 0 || strcmp(m_mode, "rb+") == 0 || strcmp(m_mode, "ab+") == 0)
    {
        m_rw = 1;
    }
}

binIO_t& binIO_t::operator>>(void* _buf)
{
    if((m_rw == 1 || m_rw == 2) && _buf)
    {
        m_loc = _buf;
        return *this;
    }
    m_status = READ_ERR;
    throw READ_ERR;
}

binIO_t& binIO_t::operator<<(const void* _buf)
{
    if((m_rw == 0 || m_rw == 2) &&_buf)
    {
        m_loc = (void*)_buf;
        return *this;
    }
    m_status = WRITE_ERR;
    throw WRITE_ERR;
}

void binIO_t::operator,(int len)
{
    if(m_rw == 0)
    {
        if(0 == fwrite(m_loc, len, 1, m_file))
        {
            m_status = WRITE_ERR;
            throw WRITE_ERR;
        }
        
    }
    else
    {
        if(0 == fread(m_loc, len, 1, m_file))
        {
            m_status = READ_ERR;
            throw READ_ERR;
        }
    }
    
    m_status = OK_E;
}












#endif /* __BINIO_T_H__ */
