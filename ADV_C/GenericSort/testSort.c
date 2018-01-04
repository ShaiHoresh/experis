#include "GSort.h"

#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */

void PrintFormat(size_t _flag);

void TestDataNULL();
void TestBlockSizeZero();
void TestEmptyArray();
void TestNULLFunc();

void TestOneElementAscendingInt();
void TestAscendingintNormalInt();

void TestOneElementDescendingInt();
void TestDescendingNormalInt();

void TestOneElementAscendingChar();
void TestAscendingNormalChar();

void TestOneElementDescendingChar();
void TestDescendingNormalChar();


void TestDigitsSumOneElement();
void TestDigitsSumNormal();

void TestPersonIDOneElement();
void TestPersonIDNormal();

struct Person
{
    int 	m_id;
    char* 	m_name;
};

typedef struct Person Person;

int PersonIdInc(const void* _first, const void* _second)
{
    Person* fir;
    Person* sec;
    
    fir = (Person*)_first;
    sec = (Person*)_second;
    
    return(fir->m_id > sec->m_id);
}

int Inc(const void* _first, const void* _second)
{
    return(*(int*)_first > *(int*)_second);
}

int Dec(const void* _first, const void* _second)
{
    return(*(int*)_first <= *(int*)_second);
}

int DigitsSum(const void* _first, const void* _second)
{
    int a, b, sumFirst = 0, sumSec = 0;
    a = *(int*)_first;
    b = *(int*)_second;
    
    while(a > 0)
    {
        sumFirst += a % 10;
        a /= 10;
    }
    while(b > 0)
    {
        sumSec += b % 10;
        b /= 10;
    }
    
    return (sumFirst > sumSec);
}

int IncChars(const void* _first, const void* _second)
{
    return(*(char*)_first > *(char*)_second);
}

int DecChars(const void* _first, const void* _second)
{
    return(*(char*)_first <= *(char*)_second);
}

int main()
{
    TestDataNULL();
    TestBlockSizeZero();
    TestEmptyArray();
    TestNULLFunc();;

    TestOneElementAscendingInt();
    TestAscendingintNormalInt();

    TestOneElementDescendingInt();
    TestDescendingNormalInt();

    TestOneElementAscendingChar();
    TestAscendingNormalChar();

    TestOneElementDescendingChar();
    TestDescendingNormalChar();

    TestDigitsSumOneElement();
    TestDigitsSumNormal();

    TestPersonIDOneElement();
    TestPersonIDNormal();

    return 0;
}

void TestDataNULL()
{
    ADTErr error;
    
    error = GenericBubbleSort(NULL, 5, sizeof(int), Inc);
    PrintFormat(!error);
    printf("data is NULL\n");
}

void TestBlockSizeZero()
{
    ADTErr error;
    int arr[5] = {1 ,2 ,3 ,4 ,5};
    
    error = GenericBubbleSort(arr, 5, 0, Inc);
    PrintFormat(!error);
    printf("Block size is 0\n");
}

void TestEmptyArray()
{
    ADTErr error;
    int arr[0];
    
    error = GenericBubbleSort(arr, 0, sizeof(int), Inc);
    PrintFormat(error);
    printf("Empty Array\n");
}

void TestNULLFunc()
{
    ADTErr error;
    int arr[5] = {1 ,2 ,3 ,4 ,5};
    
    error = GenericBubbleSort(arr, 5, sizeof(int), NULL);
    PrintFormat(!error);
    printf("NULL function\n");
}

void TestOneElementAscendingInt()
{
    ADTErr error;
    int arr[1] = {1};
    
    error = GenericBubbleSort(arr, 1, sizeof(int), Inc);
    PrintFormat(error);
    printf("One element ascending int\n");
}

void TestAscendingintNormalInt()
{
    ADTErr error;
    int arr[5] = {1 ,8 ,3 ,2 ,5};
    
    error = GenericBubbleSort(arr, 5, sizeof(int), Inc);
    PrintFormat(error);
    printf("Ascending normal int\n");

}

void TestOneElementDescendingInt()
{
    ADTErr error;
    int arr[1] = {1};
    
    error = GenericBubbleSort(arr, 1, sizeof(int), Dec);
    PrintFormat(error);
    printf("One element Descending int\n");
}

void TestDescendingNormalInt()
{
    ADTErr error;
    int arr[5] = {1 ,2 ,3 ,4 ,5};
    
    error = GenericBubbleSort(arr, 5, sizeof(int), Dec);
    PrintFormat(error);
    printf("Descending normal int\n");
}

void TestOneElementAscendingChar()
{
    ADTErr error;
    char str[4] = {'Y'};
    
    error = GenericBubbleSort(str, 1, sizeof(char), IncChars);
    PrintFormat(error);
    printf("One element Ascending char\n");
}

void TestAscendingNormalChar()
{
    ADTErr error;
    char str[4] = {'Y', 'o', 's', 'i'};
    
    error = GenericBubbleSort(str, 4, sizeof(char), IncChars);
    PrintFormat(error);
    printf("Normal Ascending char\n");
}


void TestOneElementDescendingChar()
{
    ADTErr error;
    char str[4] = {'Y'};
    
    error = GenericBubbleSort(str, 1, sizeof(char), DecChars);
    PrintFormat(error);
    printf("One element Descending char\n");
}

void TestDescendingNormalChar()
{
    ADTErr error;
    char str[4] = {'Y', 'o', 's', 'i'};
    
    error = GenericBubbleSort(str, 4, sizeof(char), DecChars);
    PrintFormat(error);
    printf("Normal Descending char\n");
}

void TestDigitsSumNormal()
{
    ADTErr error;
    int arr[5] = {124 ,322 ,1253 ,54 ,645};
    
    error = GenericBubbleSort(arr, 5, sizeof(int), Dec);
    PrintFormat(error);
    printf("Normal digits sum\n");
}

void TestDigitsSumOneElement()
{
    ADTErr error;
    int arr[5] = {124};
    
    error = GenericBubbleSort(arr, 1, sizeof(int), Dec);
    PrintFormat(error);
    printf("One element digits sum\n");
}

void TestPersonIDOneElement()
{
    ADTErr error;
    Person person[1];
    
    person[0].m_id = 123;
    person[0].m_name = "shlomi";
    
    error = GenericBubbleSort(person, 1, sizeof(Person), PersonIdInc);
    
    PrintFormat(error);
    printf("Persons ID one element\n");
}

void TestPersonIDNormal()
{
    ADTErr error;
    
    Person persons[5];
    
    persons[0].m_id = 123;
    persons[0].m_name = "shlomi";
    persons[1].m_id = 355;
    persons[1].m_name = "shlomo";
    persons[2].m_id = 13;
    persons[2].m_name = "Haim";
    persons[3].m_id = 152;
    persons[3].m_name = "David";
    persons[4].m_id = 45;
    persons[4].m_name = "Yosi";
    
    error = GenericBubbleSort(persons, 5, sizeof(Person), PersonIdInc);
    
    PrintFormat(error);
    printf("Persons ID normal \"array\"\n");
}


void PrintFormat(size_t _flag)
{
    if(_flag == 0)
    {
        printf("SUCCEEDED:  ");
    }
    else
    {
        printf("FAILED:     ");
    }
}
