/*#include "Bank.h"

int main()
{
    Bank& bank = Bank::CreateBank();
    return 0;
}
*/

#include <string>
#include <iostream>

#include "Bank.h"
using namespace std;

int main()
{
	bool isRunning = true;
	int input,action;
	string type;
	
	
	Bank& bank = Bank::CreateBank();
	while(isRunning)
	{
		cout << "1) would you like to open an account? "<< endl;
		cout << "2) would you like to Notifyc accounts?"<< endl;
		cout << "3) Number of accounts in bank"<< endl;
		cin >> input;
		if(input==1)
		{
			cout << "which Account would you wont to open?" << endl;
			cout << "1) Personal Account" << endl;
			cout << "2) Family Account" << endl;
			cout << "3) Stock Account" << endl;
			cout << "4) close" << endl;
			cout << "5) Test wrong account type" << endl;
			cin >> action;
			switch (action) 
			    {
			        ;
			        case 1:
			        	type="Saving";
			            break;                    
			        case 2:
			        	type="Family";
			            break;
			        case 3:
			        	type="Stock";
			            break;
					case 4:		            
			            isRunning=false;
			            break;
			        case 5:		            
						type="yossi";
						break;
			        default:
			            return 0;
			    }
			bank.OpenAccount(type);
		}
		else if(input==2)
		{
			cout << "to wetch accouts you would like to send message to?" << endl;
			cout << "1) Personal Account" << endl;
			cout << "2) Family Account" << endl;
			cout << "3) Stock Account" << endl;
			cout << "4) All Account" << endl;
			cin >> action;
			switch (action) 
			    {
			        ;
			        case 1:
			        	bank.Meeting();
			            break;                    
			        case 2:
			        	bank.GiveBonus();
			            break;
			        case 3:
			        	bank.Invest();
			            break;
		            case 4:
		            	type="All";
		            	break;
			        default:
			            return 0;
			    }
			//bank.Notify(type);
		}
		else
		cout<<bank.GetNumOfAcc()<<endl;
	}
	return 1;
}

