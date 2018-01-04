#include "BigNums.h"

int main()
{
    /*BigNumber bn1("99");
    BigNumber bn2("10");
    BigNumber bn3;
    
    cout << bn2 << endl;
    cout << bn2 << ">" <<bn1 << "? " << (bn2 > bn1) << endl;
    cout << bn2 << "<" <<bn1 << "? " << (bn2 < bn1) << endl;
    
    cin >> bn3;
    cout << bn3 << endl;
    
    bn3 = bn1 + bn2;
    cout << bn3 << endl;
    
    BigNumber bn4 = "21644413546598";
    BigNumber bn5 = "96385265487513218464";
    bn3 = bn4 - bn5;
    cout << bn3 << endl;*/
    
    BigNumber n1, n2;
    
    int option;
    bool flag = true;
    while(flag)
    {
        cout << "\n\n\nPlease choose option:" << endl;
        cout << "\t1. assign a new number (n1)" << endl;
        cout << "\t2. assign a new number (n2)" << endl;
        cout << "\t3. n1 + n2" << endl;
        cout << "\t4. n1 - n2" << endl;
        cout << "\t5. n1 > n2 ?" << endl;
        cout << "\t6. n1 < n2 ?" << endl;
        cout << "\t7. n1 == n2 ?" << endl;
        cout << "\t8. print n1" << endl;
        cout << "\t9. print n2" << endl;
        cin >> option;
        
        switch(option)
        {
            case 1:
                cin >> n1;
            break;
            case 2:
                cin >> n2;
            break;
            case 3:
                cout << (n1 + n2) << endl;
            break;
            case 4:
                cout << (n1 - n2) << endl;
            break;
            case 5:
                cout << (n1 > n2) << endl;
            break;
            case 6:
                cout << (n1 < n2) << endl;
            break;
            case 7:
                cout << (n1 == n2) << endl;
            break;
            case 8:
                cout << n1 << endl;
            break;
            case 9:
                cout << n2 << endl;
            break;
            default:
                flag = false;
            break;
        
        }
        
    }
    
    
    
    return 0;
}



