#include <iostream>


#include "tContainers.h"

int main()
{
//    tContainers<int, list<int*> > arr;
    tContainers<int, list<int*> > arr;
    cout << "array is still empty: " << arr.Empty() << endl;
    
    int *y = new int;
    int *a = new int;
    int *b = new int;
    *y = 3;
    *a = 87;
    *b = 98;
    arr.PushBack(*y);
    arr.PushBack(*a);
    arr.PushBack(*b);
    
    cout << "I found that b = " << *(arr.Find(87)) << endl;
    
    int* c = arr.Remove(*b);
    arr.RemoveDelete(*b);

    cout << arr[0] << " " << arr[77]/* << " " << arr[2]*/ << endl;
    cout << arr.Size() << endl;
    
    arr.RemoveDeleteAll();
    cout << arr.Size() << endl;
    
    
    return 0;
}
