#ifndef __LINKED_H__
#define __LINKED_H__

#define NAME_SIZE 128

typedef struct Person Person;

struct Person
{
	int 	m_id;
	char 	m_name[NAME_SIZE];
	int 	m_age;
	Person* m_next;
};


/*

*/
Person * ListInsertHead(Person* _head, Person* _p);
/*

*/
Person * ListRemoveHead(Person* _head, Person** _item);
/*

*/
Person * ListInsertByKey(Person* _head, int _key, Person* _p);
/*

*/
Person * ListInsertByKeyRec(Person* _head, int _key, Person* _p);
/*

*/
Person * ListRemoveByKey(Person* _head, int _key, Person** _p);



Person * ListRemoveByKeyRec(Person* _head, int _key, Person** _p);

Person* ListFindTailRec(Person* _head);

void 	PrintList(Person * _head);
#endif /* endif __LINKED_H__ */
