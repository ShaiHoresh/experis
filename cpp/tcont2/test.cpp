#include <iostream>


#include "tContainers2.h"

int main()
{
//    tContainers<int, list> arr;
    tContainers<int, list> arr;
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
    
    cout << "I found that b = " << arr.Find(87) << endl;
    
    int c = arr.Remove(*b);
    arr.RemoveDelete(*b);

    cout << arr[0] << " " << arr[1] << endl;
    cout << arr.Size() << endl;
    
    arr.RemoveDeleteAll();
    cout << arr.Size() << endl;
    
  
    return 0;
}
