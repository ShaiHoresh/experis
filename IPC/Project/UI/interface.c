#include <stdio.h>
#include "ui.h"



int main(int argc, char *argv[])
{
    unsigned int req, tuple;
    char msisdn[16];
    int flag = 1;
    
    while(flag)
    {
        printf("Please insert your query:\n \t1: Retrieve One Subscriber Data\n\t2: Retrieve One Operator\n\t3: Retrieve All Subscribers\n\t4: Retrieve All Operators\n\t5: Retrieve Aggregated Data\n\t6: stop and close everything\n\t10: close GUI\n");
        scanf("%d", &req);
    
        switch(req)
        {
            case 1:
                printf("Please enter the subscriber msisdn: ");
                scanf("%s", msisdn);
                RetrieveSubscriber(msisdn);
            break;
            case 2:
                printf("Please enter operator tuple: ");
                scanf("%u", &tuple);
                RetrieveOperator(tuple);
            break;
            case 3:
                RetrieveAllSubscribers();
            break;
            case 4:
                RetrieveAllOperator();
            break;
            case 5:
                RetrieveAggregatedData();
            break;
            case 6:
                CloseEverything();
            break;
            case 10:
                flag = 0;
            break;
            default:
                printf("Sorry. Wrong command\n");
            break;
        }
    }
    
    return 0;
}

