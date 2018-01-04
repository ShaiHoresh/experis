#include <iostream> /*cin, cout*/
#include <iomanip> /*setw, setfill*/
#include <fstream> /*ofstream*/

//#include <string>

using namespace std; /*string, cin, cout, opfstream, endl, ofstream, setw, left, setfill*/

ostream& printline(ostream& os)
{
    return (os << endl << "_____________________________" << endl);
}

int main()
{
    string id1, id2, name1, name2;
    ofstream outS("trial");
    
    cout << "Please enter ID1" << endl;
    cin >> id1;
    cout << "Please enter name1" << endl;
    cin >> name1;
    cout << "Please enter ID2" << endl;
    cin >> id2;
    cout << "Please enter name2" << endl;
    cin >> name2;
    
    outS << printline << setw(10) << setfill('.') << left << id1 << setw(20) << name1 << printline << setw(10) << setfill('.') << id2 << setw(20) << name2 << printline;
    
    return 0;
}
