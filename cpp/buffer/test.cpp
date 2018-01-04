#include <stdio.h>
#include <iostream>
using namespace std;

#include "mystring.h"

int main()
{
    int flag = 1, option;
    char buffer[128];
    String_t s2("example"), s1("Example");
//    String_t s3 = s1;    
    int res;
    int cmp;
    
    while(flag)
    {
        cout << "\n\n\nPlease choose option:" << endl;
        cout << "\t1. Check length" << endl;
        cout << "\t2. Set" << endl;
        cout << "\t3. Get" << endl;
        cout << "\t4. Compare" << endl;
        cout << "\t5. Upper" << endl;
        cout << "\t6. Lower" << endl;
        cout << "\t7. Prepend from char*" << endl;
        cout << "\t8. Prepend from object" << endl;
        cout << "\t9. Contains" << endl;
        cout << "\t10. operator <" << endl;
        cout << "\t11. operator ==" << endl;
        cout << "\t12. get capacity" << endl;
        cout << "\t13. set capacity" << endl;
        cout << "\t14. case sensitive?" << endl;
        cout << "\t15. set case sensitivity" << endl;
        cout << "\t16. first occurrence" << endl;
        cout << "\t17. last occurrence" << endl;
        cout << "\t18. operator ()" << endl;
        cout << "\telse: I want to stop!" << endl;
        
        cin >> option;
        
        switch(option)
        {
            case 1:
                cout << "the length of the string is "<< s2.GetSize() << endl;
            break;  
            case 2:
                cout << "please enter a string" << endl;
                cin >> buffer;
                s2.Set(buffer);
                cout << s2 << "" << endl;
            break;
            case 3:
                cout << s2.Get() << "" << endl;
            break;
            case 4:
                cmp = s2.Compare(s1);
                if(0 == cmp)
                {
                    cout << "equal" << endl;
                }
                else if(1 == cmp)
                {
                    cout << "smaller" << endl;
                }
                else
                {
                    cout << "bigger" << endl;
                }
            break;
            case 5:
                s2.Upper();
                cout << s2 << "" << endl;
            break;
            case 6:
                s2.Lower();
                cout << s2 << "" << endl;
            break;
            case 7:
                cout << "please enter a string" << endl;
                cin >> buffer;
                s2.Prepend(buffer);
                cout << s2 << "" << endl;
            break;
            case 8:
                s2.Prepend(s1);
                cout << s2 << "" << endl;
            break;
            case 9:
                cout << "please enter the substring" << endl;
                cin >> buffer;
                res = s2.Contains(buffer);
                if(res == 1)
                {
                    cout << "substring found (-;" << endl;
                }
                else
                {
                    cout << "substring not found )-;" << endl;
                }
            break;
            case 10:
                cout << "s1 < s2? " << (s1 < s2) << "" << endl;
            break;
            case 11:
                cout << "s1 == s2? " << (s1 == s2) << "" << endl;
            break;
            case 12:
                cout << "size is: " << s1.GetSize() << endl;
            break;
            case 13:
                cout << "want to change capacity to 23" << endl;
                cout << "previous capacity is: " << s1.ReSize(23) << endl;
                cout << "new capacity is: " << s1.GetSize() << endl;
            break;
            case 14:
                cout << "case sensitivity is on? " << s1.GetCaseSens() << endl;
            break;
            case 15:
                cout << "turning on " << endl;
                s1.SetCaseSens(true);
                cout << "case sensitivity is on? " << s1.GetCaseSens() << endl;
                cout << "turning off " << endl;
                s1.SetCaseSens(false);
                cout << "case sensitivity is on? " << s1.GetCaseSens() << endl;
            break;
            case 16:
                cout << "first occurrence of \'e\': " << s1.FirstOccurrence('e');
            break;
            case 17:
                cout << "last occurrence of \'e\': " << s1.LastOccurrence('e');
            break;
            case 18:
                cout << "substring of \"example\", from 3 to 5 is " << s1(3, 2);
            break;
            default:
                flag = 0;
            break;
        }
    }
    
    
    
    return 0;
}





































/*
int main()
{
    String_t s1;
    s1.Set("Shalom uVracha\n");
    String_t s2("Shalom, Olam!!\n");
    
    const char* getter = s1.Get();
    printf("%s", getter);
    String_t s2 = s1;
    printf("printing 3 strings\ns1: ");
    s1.Print();
    printf("s2: ");
    s2.Print();
    printf("s2: ");
    s2.Print();
    
    int res = s1.Set("Great!!\n");
    printf("s1 - %d: ", res);
    s1.Print();
    
    res = s2.Compare(s2);
    printf("comparison = %d\n", res);
    
    printf("length = %u\n", s2.Length());
    
    printf("s1: ");
    s1.Print();
    s1.Upper();
    printf("upper: ");
    s1.Print(); 
    
    s1.Lower();
    printf("lower: ");
    s1.Print(); 
    
    s1.Prepend("That's ");
    printf("prepend: ");
    s1.Print();
    
    res = s1.Contains("gre");
    printf("is \"gre\" in the string? %d\n", res);
    res = s1.Contains("grate");
    printf("and what about \"grate\"? %d\n", res);
    
    printf("s1 & s2: ");
    s1.Print();
    s2.Print();
    
    s1 += s2;
    s1.Print();
    
    printf("s1 < s2? %d\n", s1 < s2);
    printf("s1 > s2? %d\n", s1 > s2);
    printf("s1 >= s2? %d\n", s1 >= s2);
    printf("s1 <= s2? %d\n", s1 <= s2);
    printf("s1 != s2? %d\n", s1 != s2);
    
    String_t s4;
    
    cin >> s4;
    cout << s4;
    
    printf("\n%c\n", s4[3]);
    printf("\n%c\n", s4[20]);
    
    return 0;
}*/
