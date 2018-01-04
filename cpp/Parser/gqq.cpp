#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, const char* argv[])
{
    Parser p;
    
    cout << endl;
    for (int i = 1; i < argc; ++i)
    {
        cout << "working on file: " << argv[i] << endl;
        p.Parse(argv[i]);
        cout << endl;
    }
    return 0;
}
