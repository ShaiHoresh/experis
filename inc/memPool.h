#ifndef __MEMPOOL_T_H__
#define __MEMPOOL_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "memManager.h"
#include "memPage.h"
#include <vector>
//using namespace std;

class MemPool_t: public MemManager_t
{
public:
            //CTORs, DTOR
    MemPool_t();
    virtual ~MemPool_t();

    virtual size_t Read(void** _buf, unsigned int _size);
    virtual size_t Read(void** _buf, size_t _pos, unsigned int _size);
    virtual size_t Write(const void* _data, unsigned int _size);
    virtual size_t Write(const void* _data, unsigned int _size ,size_t _pos);
    
private:    // dummy functions
    MemPool_t(const MemPool_t& _page);
    const MemPool_t& operator=(const MemPool_t& _page);
            
            // auxiliary funcs
    size_t FindPage(size_t _page, size_t* _position);
    void AddPage();

            // data
protected:
    std::vector<MemPage_t*> m_vec;
};


#endif /* __MEMPOOL_T_H__ */
