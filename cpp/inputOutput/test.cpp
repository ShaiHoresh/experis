#include "virtIO_t.h"
#include "asciiIO_t.h"
#include "binIO_t.h"


#include <iostream>
using namespace std;

/*
int main()
{
    asciiIO_t x("trial", "w");
    binIO_t b("binTrial", "wb");
    
    int i = 8, j = 0;
    double d = 3.14, e = 0.0;
    char c = ' ', q, w, t, r;
    b << 'H' << 'a' << 'n' << 'a';
    
    x << i << c << d;
    
    x.SetAccess("r");
    x >> j >> e;
    
    std::cout << endl << j << endl << e << endl;
    
    b << i << c << d;
    char buf[8] = "Shalom";
    b << buf, 6;
    
    b.SetAccess("rb");
    b >> q >> w >> t >> r >> j >> c >> e;
    
    char newbuf[8];
    b >> newbuf, 6;
    std::cout << endl << "file length: " << b.Length() << endl;
    
    std::cout << q << w << t << r << endl << j << endl << e << endl;
    std::cout << newbuf;
    return 0;
}
*/

int main()
{
    bool cont = true, same = true, def = true;    
    char rw;
    char fileName[32], mode[3];
    binIO_t* bp;
    
    virtIO_t* f = 0;
    
    bool m = true;
    while(m)
    {
        cout << "Please enter file name" << endl;
        cin >> fileName;
    
        cout << "Please enter read/write mode" << endl;
        cin >> mode;
        m = false;
        if(mode[1] == 'b')
        {
            try{f = new binIO_t(fileName, mode);}
            catch(Status _st)
            {
                if(_st == CANT_OPEN_FILE)
                {
                    cout << "couldn't open file" << endl;
                    m = true;
                }
            }
        }
        else
        {
            try{f = new asciiIO_t(fileName, mode);}
            catch(Status _st)
            {
                if(_st == CANT_OPEN_FILE)
                {
                    cout << "couldn't open file" << endl;
                    m = true;
                }
            }
        }
    }
    
    while(cont)
    {
        
        cout << "do you want to write[0] or to read[1]?" << endl;
        cin >> def;
        
        if(!def)
        {
            while(same)
            {
                cout << "(i)nt | (c)har | (d)ouble | {in binary - (v)oid*} | (b)reak" << endl;
                
                cin >> rw;
                switch(rw)
                {
                    case 'i':
                        int i;
                        try
                        {
                            cin >> i;
                        }
                        catch(Status _st)
                        {
                            if(_st == WRITE_ERR)
                            {
                                cout << "bad status" << endl;
                            }
                        }
                        *f << i;
                    break;
                    case 'c':
                        char c;
                        try
                        {
                            cin >> c;
                        }
                        catch(Status _st)
                        {
                            if(_st == WRITE_ERR)
                            {
                                cout << "bad status" << endl;
                            }
                        }
                        *f << c;
                    break;
                    case 'd':
                        double d;
                        try
                        {
                            cin >> d;
                        }
                        catch(Status _st)
                        {
                            if(_st == WRITE_ERR)
                            {
                                cout << "bad status" << endl;
                            }
                        }
                        *f << d;
                    break;
                    case 'b':
                        same = false;
                    break;
                    case 'v':
                        bp = dynamic_cast<binIO_t*>(f);
                        if(bp != 0)
                        {
                            char buf[32] = {0};
                            cin >> buf;
                            cout << "enter num of bytes" << endl;
                            int size;
                            cin >> size;
                            try{ (*(binIO_t*)f) << (const void*)buf, size; }
                            catch(Status _st)
                            {
                                if(_st == WRITE_ERR)
                                {
                                    cout << "bad status" << endl;
                                }
                            }
                        }
                        else
                        {
                            cout << "you are in ascii mode" << endl;
                        }
                    break;
                    default:
                        same = false;
                    break;
                }
            }
        }
        else
        {
            while(same)
            {
                cout << "(i)nt | (c)har | (d)ouble | {in binary - (v)oid*} | (b)reak" << endl;
                
                cin >> rw;
                switch(rw)
                {
                    case 'i':
                        int i;
                        try{(*f) >> i;}
                        catch(Status _st)
                        {
                            if(_st == READ_ERR)
                            {
                                cout << "bad status" << endl;
                            }
                        }
                        cout << i << endl;
                    break;
                    case 'c':
                        char c;
                        try{(*f) >> c;}
                        catch(Status _st)
                        {
                            if(_st == READ_ERR)
                            {
                                cout << "bad status" << endl;
                            }
                        }
                        cout << c << endl;
                    break;
                    case 'd':
                        double d;
                        try{(*f) >> d;}
                        catch(Status _st)
                        {
                            if(_st == READ_ERR)
                            {
                                cout << "bad status" << endl;
                            }
                        }
                        cout << d << endl;
                    break;
                    case 'v':
                        bp = dynamic_cast<binIO_t*>(f);
                        if(bp != 0)
                        {
                            cout << "How many bytes do you want to read? " << endl;
                            int size;
                            cin >> size;
                            char buf[32] = {0};
                            try{*(binIO_t*)f >> buf, size;}
                            catch(Status _st)
                            {
                                if(_st == READ_ERR)
                                {
                                    cout << "bad status" << endl;
                                }
                            }
                            cout << buf << endl;
                        }
                        else
                        {
                            cout << "you are in ascii mode" << endl;
                        }
                    break;
                    default:
                        same = false;
                    break;
                }
            }
        }
        cout << "do you want to continue? (1 = yes, 0 = stop)" << endl;
        cin >> cont;
        if(cont)
        {
            same = true;
            cout << "do you want to change w/r mode? (1 = yes, 0 = no)" << endl;
            bool ret;
            cin >> ret;
            if(ret)
            {
                cout << "enter the new mode" << endl;
                char mode[3];
                cin >> mode;
                m = true;
                while(m)
                {
                    m = false;
                    if(mode[1] == 'b')
                    {
                        try
                        {
                            f->Close();
                            f = new binIO_t(fileName, mode);
                        }
                        catch(Status _st)
                        {
                            if(_st == CANT_OPEN_FILE)
                            {
                                cout << "couldn't open file" << endl;
                                m = true;
                            }
                        }
                    }
                    else
                    {
                        try{f = new asciiIO_t(fileName, mode);}
                        catch(Status _st)
                        {
                            if(_st == CANT_OPEN_FILE)
                            {
                                cout << "couldn't open file" << endl;
                                m = true;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            same = false;
        }
    }
    
    return 0;
}





















