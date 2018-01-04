#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
    Vector<int> vec;
    
    int* x = new int;
    *x = 5;
    int* y = new int;
    *y = 6;
    int* z = new int;
    *z = 34;
    int* q = new int;
    *q = 1;
    
    vec.Insert(x);
/*    vec.Insert(y);
    vec.Insert(z);
    vec.Insert(q);
*/  vec.Append(y,0);
    vec.Append(z,0);
    vec.Prepend(q,0);
    cout << vec.Contains(22) << endl;
    cout << vec.Index(34) << endl;
    cout << vec.Index(1) << endl;
    cout << vec.Index(6) << endl;
    cout << vec.Index(5) << endl;

    return 0;

}
