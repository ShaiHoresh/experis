#include <stdio.h>

#include "linked.h"

int main()
{
    
    Person p1={111, "aaaa", 1, NULL};
    Person p2={222, "bbbb", 2, NULL};
    Person p3={333, "cccc", 3, NULL};
    Person p4={444, "dddd", 4, NULL};
    Person p9={111, "aaaa", 1, NULL};
    Person* Tail = NULL;
    
    Person* head = NULL, *p5 = NULL, *p6 = NULL, *p7 = NULL, *p8 = NULL, *p11 = NULL;
    Person *p10;

    head = ListInsertHead(head, &p2);
    printf("\nlist after head (222) insertion:\n");
    PrintList(head);
    
    head = ListInsertByKey(head, p1.m_id, &p1);
    printf("list after 2nd (111) insertion:\n");
    PrintList(head);

    printf("Insert cell 444\n");
    head = ListInsertByKey(head, p4.m_id, &p4);
    printf("\nlist after 3rd insertion:\n");
    PrintList(head);

    printf("Insert cell 333\n");
    head = ListInsertByKey(head, p3.m_id, &p3);
    printf("\nlist after 4th insertion:\n");
    PrintList(head);
/**************************************************/
    printf("Remove head!\n");
    head = ListRemoveHead(head, &p8);
    PrintList(p8);
    printf("Remove head!\n");
    head = ListRemoveHead(head, &p8);
    PrintList(p8);
    printf("Remove head!\n");
    head = ListRemoveHead(head, &p8);
    PrintList(p8);
    printf("Remove head!\n");
    head = ListRemoveHead(head, &p8);
    PrintList(p8);
    printf("Remove head!\n");
    head = ListRemoveHead(head, &p8);
    PrintList(p8);
    printf("\nupdated list is(nothing)\n");
    PrintList(head);

    head = ListInsertByKey(head, p9.m_id, &p9);
    printf("\nlist after head insertion:\n");
    PrintList(head);    
/**************************************************/
    head = ListRemoveByKey(head, 777, &p5);
    printf("\np5(111) = ");
    PrintList(p5);
    printf("\nupdated list is(2 3 4)\n");
    PrintList(head);
 
    head = ListInsertByKeyRec(head, p1.m_id, &p1);
    printf("\nlist after recursive insertion(1 2 3 4):\n");
    PrintList(head);
    
    Tail = ListFindTailRec(head);
    printf("the tail is: ");
    PrintList(Tail);
/**************************************************/
    head = ListRemoveByKey(head, 222, &p6);
    printf("\np6(222) = ");
    PrintList(p6);
    printf("\nupdated list is(1)\n");
    PrintList(head);
    
    head = ListInsertByKeyRec(head, p2.m_id, &p2);
    printf("\nlist after recursive insertion(1 2):\n");
    PrintList(head);
/**************************************************/
    head = ListRemoveByKey(head, 111, &p7);
    printf("\np7 = ");
    PrintList(p7);
    printf("\nupdated list is(2)\n");
    PrintList(head);
    
    head = ListInsertByKeyRec(head, p4.m_id, &p4);
    printf("\nlist after recursive insertion(1 2 3 4):\n");
    PrintList(head);
    printf("***************************************");
    head = ListInsertByKeyRec(head, p1.m_id, &p1);
    printf("\nlist after recursive insertion:\n");
    PrintList(head);
/**************************************************/
/**************************************************/
    head = ListRemoveByKeyRec(head, 111, &p10);
    printf("\np6(2) = ");
    PrintList(p10);
    printf("\nlist after recursive remove\n");
    PrintList(head);
    
    head = ListInsertByKeyRec(head, p2.m_id, &p2);
    printf("\nlist after recursive insertion:\n");
    PrintList(head);
    head = ListInsertByKeyRec(head, p3.m_id, &p3);
    printf("\nlist after recursive insertion:\n");
    PrintList(head);
    head = ListInsertByKeyRec(head, p1.m_id, &p1);
    printf("\nlist after recursive insertion:\n");
    PrintList(head);
/**************************************************/
    head = ListRemoveByKeyRec(head, 444, &p11);
    printf("\np11(4) = ");
    PrintList(p11);
    printf("\nlist after recursive remove\n");
    PrintList(head);
   
    head = ListInsertByKeyRec(head, 222, &p2);
    printf("\nlist after recursive insertion:\n");
    PrintList(head);
/**************************************************/
    head = ListRemoveByKeyRec(head, 111, &p7);
    printf("\np7() = ");
    PrintList(p7);
    printf("\nlist after recursive remove\n");
    PrintList(head);
    
    head = ListInsertByKeyRec(head, p4.m_id, &p4);
    printf("\nlist after recursive insertion:\n");
    PrintList(head);
/**************************************************/

    printf("\n");
    return 0;
}

/*
Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p)
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
*/
