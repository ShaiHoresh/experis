#include "ui.h"

int RetrieveSubscriber(char* _msisdn)
{
    QuerySend(1, _msisdn);
}

int RetrieveOperator(unsigned int _tuple)
{
    QuerySend(2, _tuple);
}

int RetrieveAllSubscribers()
{
    QuerySend(3, NULL);
}

int RetrieveAllOperator()
{
    QuerySend(4, NULL);
}

int RetrieveAggregatedData()
{
    QuerySend(5, NULL);
}

int CloseEverything()
{
    QuerySend(6, NULL);
}




