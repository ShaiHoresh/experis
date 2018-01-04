#ifndef __VIRTIO_T_H__
#define __VIRTIO_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <stdio.h>
#include <string.h>

using namespace std;


enum Status
{
    OK_E,
    CANT_OPEN_FILE,
    BAD_ACCESS,
    WRITE_ERR,
    READ_ERR
};

class virtIO_t
{

public:
    virtIO_t();
    virtIO_t(const char* _pathName, const char* _mode);
    virtual ~virtIO_t();
    
    long Length() const;
    Status SetPath(const char* _path);
    Status SetAccess(const char* _mode);
    void Open(const char* _pathName, const char* _mode);
    void Close() {if(m_file) fclose(m_file);}
    void Seek(unsigned int _pos){if(m_file) fseek(m_file, _pos, 0);}
    
    int GetMode() {return m_rw;}
    
    Status GetStatus() const;
    
    virtual virtIO_t& operator<<(int _i) = 0;
    virtual virtIO_t& operator<<(char _i) = 0;
    virtual virtIO_t& operator<<(short _i) = 0;
    virtual virtIO_t& operator<<(long _i) = 0;
    virtual virtIO_t& operator<<(float _i) = 0;
    virtual virtIO_t& operator<<(double _i) = 0;
    virtual virtIO_t& operator<<(unsigned int _i) = 0;
    virtual virtIO_t& operator<<(unsigned char _i) = 0;
    virtual virtIO_t& operator<<(unsigned short _i) = 0;
    virtual virtIO_t& operator<<(unsigned long _i) = 0;
     
    virtual virtIO_t& operator>>(int& _i) = 0;
    virtual virtIO_t& operator>>(char& _i) = 0;
    virtual virtIO_t& operator>>(short& _i) = 0;
    virtual virtIO_t& operator>>(long& _i) = 0;
    virtual virtIO_t& operator>>(float& _i) = 0;
    virtual virtIO_t& operator>>(double& _i) = 0;
    virtual virtIO_t& operator>>(unsigned int& _i) = 0;
    virtual virtIO_t& operator>>(unsigned char& _i) = 0;
    virtual virtIO_t& operator>>(unsigned short& _i) = 0;
    virtual virtIO_t& operator>>(unsigned long& _i) = 0;

    void CheckSetMode(const char* _mode);
    
protected:
    FILE* m_file;
    char m_path[64];
    char m_mode[3];
    Status m_status;
    int m_rw; // 0 for write, 1 for read, 2 for both, -1 for illegal type

private:
    virtIO_t(const virtIO_t& _io);
    virtIO_t& operator=(const virtIO_t& _io);
    
};

virtIO_t::virtIO_t()
{
    m_file = 0;
    m_path[0] = '0';
    m_mode[0] = '0';
    m_status = BAD_ACCESS;
}

virtIO_t::virtIO_t(const char* _pathName, const char* _mode)
{
    Open(_pathName, _mode);
}

void virtIO_t::Open(const char* _pathName, const char* _mode)
{
    CheckSetMode(_mode);
    if(_pathName && _mode)
    {
        m_file = fopen(_pathName, _mode);
    }
    if(0 != m_file)
    {
        m_status = OK_E; 
        strcpy(m_path, _pathName);
        strcpy(m_mode, _mode);
    }
    else
    {
        m_status = CANT_OPEN_FILE;
        throw m_status;
    }
    
}

virtIO_t::~virtIO_t()
{
    if(0 != m_file)
    {
        fclose(m_file);
    }
}

long virtIO_t::Length() const
{
    if(0 != m_file)
    {
        fseek(m_file, 0,2);
        return ftell(m_file);
    }
    
    return 0;
}

Status virtIO_t::SetPath(const char* _path)
{
    if(_path && 0 != m_file)
    {
        strcpy(m_path, _path);
        if(m_mode[0] != '0')
        {
            return OK_E;
        }
    }
    return BAD_ACCESS;
}

Status virtIO_t::SetAccess(const char* _mode)
{
    if(_mode && 0 != m_file && m_path[0] != '0')
    {
        fclose(m_file);
        m_file = fopen(m_path, _mode);
        if(0 != m_file)
        {
            strcpy(m_mode, _mode);
            return OK_E;
        }
    }
    return BAD_ACCESS;
}

inline Status virtIO_t::GetStatus() const
{
    return m_status;
}

void virtIO_t::CheckSetMode(const char* _mode)
{
    strcpy(m_mode, _mode);
    if(strcmp(m_mode, "r") == 0 || strcmp(m_mode, "rb") == 0)
    {
        m_rw = 1;
    }
    else if(strcmp(m_mode, "w") == 0 || strcmp(m_mode, "wb") == 0)
    {
        m_rw = 0;
    }
    else if(strcmp(m_mode, "r+") == 0 || strcmp(m_mode, "w+") == 0 || strcmp(m_mode, "a+") == 0 || strcmp(m_mode, "rb+") == 0 || strcmp(m_mode, "wb+") == 0 || strcmp(m_mode, "ab+") == 0)
    {
        m_rw = 2;
    }
    else
    {
        m_rw = 0;
        //throw
    }
    
}

#endif /* __VIRTIO_T_H__ */


