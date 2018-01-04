#include <stdio.h>

#include "linked.h"


Person* ListInsertHead(Person* _head, Person* _p)
{
    _head = _p;
    return _head;
}

Person* ListRemoveHead(Person* _head, Person** _item)
{
    *_item = _head;
    return _head->m_next;
}


Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
    Person *temp, *prev;
    
    temp = _head;
    if(NULL == _head->m_next)
    {
        if(_head->m_id < _key)
        {
            _p->m_next = _head;
            _head->m_next = NULL;
            return _p;
        }
        else
        {
            _head->m_next = _p;
            _p->m_next = NULL;
            return _head;
        }
    }
    while(NULL != temp->m_next)
    {
        if(temp->m_id < _key)
        {
            prev = temp;
            temp = temp->m_next;
        }
        else if (temp->m_id == _key)
        {
            return _head;
        }
        else
        {
            _p->m_next = temp;
            prev->m_next = _p;
            return _head;
        }
    }
}

/*
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{

}*/

Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
    Person *temp, *prev;
    
    temp = _head;
    while(NULL != temp->m_next)
    {
        if(temp->m_id < _key)
        {
            prev = temp;
            temp = temp->m_next;
        }
        else
        {
            prev->m_next = temp->m_next;
            return temp;
        }
    }
}


/*
Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p);


*/
void PrintList(Person* _head)
{
    Person *temp;
    temp = _head;
    do
    {
        printf("%d, %s, %d\n", temp->m_id, temp->m_name, temp->m_age);
        temp = temp->m_next;
    }while(NULL != temp->m_next);
}

/*
struct Person
{
	int 	m_id;
	char 	m_name[NAME_SIZE];
	int 	m_age;
	Person* m_next;
};*/
