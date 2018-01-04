#include <stdio.h>

#include "linked.h"

static Person *RecInsert(Person* _head, int _key, Person* _p);
static Person* RecRemove(Person* _head, int _key, Person** _p);

Person* ListInsertHead(Person* _head, Person* _p)
{
    if(NULL == _p)
    {
        return _head;
    }
    _p->m_next = _head;
    return _p;
}

Person* ListRemoveHead(Person* _head, Person** _item)
{
    if(NULL  != _item)
    {
        *_item = _head;
        if(NULL != _head && NULL != _head->m_next)
        {
            _head = _head->m_next;
        }
        else
        {
            _head = NULL;
        }
    }
    return _head;
}


Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
    Person *temp, *prev;
    
    temp = _head;
    if(NULL == _head)
    {
        _head = ListInsertHead(_head, _p);
        return _head;
    }
    if(NULL == _head->m_next)
    {
        if(_head->m_id < _key)
        {
            _head->m_next = _p;
            return _head;
        }
        else
        {
            _p->m_next = _head;
            _head->m_next = NULL;
            return _p;
        }
    }
    while(NULL != temp->m_next || temp->m_id > _key)
    {
        if(temp->m_id < _key)
        {
            prev = temp;
            temp = temp->m_next;
        }
        else
        {
            _p->m_next = temp;
            prev->m_next = _p;
            return _head;
        }
    }
    temp->m_next = _p;
    return _head;
}


Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
    if(_p != NULL)
    {
        _head = RecInsert(_head, _key, _p);
    }
    return _head;
}

static Person* RecInsert(Person* _head, int _key, Person* _p)
{
    if(NULL == _head || _head->m_id > _key)
    {
        _p->m_next = _head;
        return _p;
    }
    if(_head->m_id == _key)
    {
        return _head;
    }
    _head->m_next = RecInsert(_head->m_next, _key, _p);
    return _head;
}
Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
    Person *temp, *prev;
    
    temp = _head;
    prev = _head;
    if(_head->m_id == _key)
    {
        _head = temp->m_next;
        *_p = temp;
        (*_p)->m_next = NULL;
        return _head;
    }
    while(NULL != temp)
    {
        if(temp->m_id < _key)
        {
            prev = temp;
            temp = temp->m_next;
        }
        else
        {
            prev->m_next = temp->m_next;
            *_p = temp;
            (*_p)->m_next = NULL;
            break;
        }
    }
    return _head;
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p)
{
    if(_p != NULL)
    {
        _head = RecRemove(_head, _key, _p);
    }
    return _head;
}

static Person* RecRemove(Person* _head, int _key, Person** _p)
{
    if(NULL == _head || _head->m_id > _key)
    {
        *_p = NULL;
        return _head;
    }
    if(_head->m_id == _key)
    {
        *_p = _head;
        return _head->m_next;   
    }
    _head->m_next = RecRemove(_head->m_next, _key, _p);
    return _head;
}

Person* ListFindTailRec(Person* _head)
{
    if(NULL == _head->m_next || NULL == _head)
    {
        return _head;
    }
    _head = ListFindTailRec(_head->m_next);
    return _head;
}
/*
Person* ReverseRec(Person* _head)

static Person* ReverseListRec(Person* _head)*/

void PrintList(Person* _head)
{
    Person *temp;
    if(NULL == _head)
    {
        return;
    }    
    temp = _head;
    do
    {
        printf("%d, %s, %d\n", temp->m_id, temp->m_name, temp->m_age);
        temp = temp->m_next;
    }while(NULL != temp);
}

/*
struct Person
{
	int 	m_id;
	char 	m_name[NAME_SIZE];
	int 	m_age;
	Person* m_next;
};*/
