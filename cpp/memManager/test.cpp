#include <iostream>
using namespace std;

//#include "memPage.h"
#include "memPool.h"



int main()
{
    MemPool_t page;
//    MemPage_t page(2);
    const char* buffer("Hello world!!");
    char* buf = new char[13];
    
    // w/o position
    cout << "write: " << page.Write(buffer, sizeof(buffer)) << endl;
    cout << "used memory: " << page.GetSize() << endl;
/*    cout << "read: " << page.Read((void**)&buf, 0, 13) << " " << buf << endl;
    cout << "used memory: " << page.GetSize() << endl;
*/    
    // w/ position
    cout << "write: " << page.Write(buffer, 5, 1) << endl;
    cout << "used memory: " << page.GetSize() << endl;
    cout << "read: " << page.Read((void**)&buf, 12) << " " << buf << endl;
    cout << "used memory: " << page.GetSize() << endl;
    
//    cout << "Is full? " << page.IsFull() << endl;
//    cout << "Is empty? " << page.IsEmpty() << endl;
    
    try
    {
        bool ret = page.SetPosition(1);
    }
    catch(const char*)
    {
        cout << "Very bad position...\n";
    }
    
    cout << "HAHAHA\n";
    
    return 0;
}
