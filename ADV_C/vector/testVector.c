#include <stdio.h>  /* printf */
#include <stdlib.h> /* free */
#include "../../inc/vector.h"
#include "../../inc/mu_test.h"



/**********************************************/
int ElementPrintInt(void* _element, void* _context)
{
    printf("%d ", *(int*)_element);
/*    printf("%x ", _element);*/
    return 1;
}

int ElementPrintChar(void* _element, void* _context)
{
    printf("%c ", *(char*)_element);
    return 1;
}

int ElementPrintStr(void* _element, void* _context)
{
    puts(*(char**)_element);
    return 1;
}

int destroyIntElement(void* _element, void* _context)
{
    free(_element);
    /*_element = NULL;*/
    return 1;
}

UNIT(Create_Normal)
	Vector* vector;
	vector = VectorCreate(5, 3);
    ASSERT_THAT(vector != NULL);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Create_Zero_Init)
	Vector* vector;
	vector = VectorCreate(0, 3);
    ASSERT_THAT(vector != NULL);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Create_Zero_Extend)
	Vector* vector;
	vector = VectorCreate(5, 0);
    ASSERT_THAT(vector != NULL);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Create_Zero_Init_And_Extend)
	Vector* vector;
	vector = VectorCreate(0, 0);
    ASSERT_THAT(vector == NULL);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_Normal_Int)
	Vector* vector;
	ADTErr flag;
	
	int *pb, *pc;
	vector = VectorCreate(3, 3);

    pb = malloc(sizeof(int));
    pc = malloc(sizeof(int));

    *pb = 1;
    *pc = 2;
    
    flag = VectorAppend(vector, pb);
    flag = VectorAppend(vector, pc);
    ASSERT_THAT(!flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_Normal_Char)
	Vector* vector;
	ADTErr flag;
	
	char c = 'g', d = 'f';
	char* p = &c, *p2 = &d;	
	
	vector = VectorCreate(5, 3);
	VectorAppend(vector, p2);
	
	flag = VectorAppend(vector, p);

    ASSERT_THAT(!flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_Normal_Str)
	Vector* vector;
	ADTErr flag;
	
	char* c = "blabla";
	char** p = &c;	
	
	vector = VectorCreate(5, 3);
	flag = VectorAppend(vector, p);
	
	ASSERT_THAT(!flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_And_Extend)
	Vector* vector;
	ADTErr flag;
	
	int *pb, *pf, *pc, *pd, *pe;
	vector = VectorCreate(3, 3);

    pb = malloc(sizeof(int));
    pc = malloc(sizeof(int));
    pd = malloc(sizeof(int));
    pe = malloc(sizeof(int));
    pf = malloc(sizeof(int));
    
    *pb = 6;
    *pc = 8;
    *pd = 7;
    *pe = 2;
    *pf = 5;
    
    flag = VectorAppend(vector, pb);
    flag = VectorAppend(vector, pc);
    flag = VectorAppend(vector, pd);	
    flag = VectorAppend(vector, pe);
    flag = VectorAppend(vector, pf);

    ASSERT_THAT(!flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_To_Init_Size_Zero)
    Vector* vector;
	ADTErr flag;
	
	int *pb, *pc;

	vector = VectorCreate(0, 3);

    pb = malloc(sizeof(int));
    pc = malloc(sizeof(int));

    *pb = 8;
    *pc = 21;
    
    flag = VectorAppend(vector, pb);
    flag = VectorAppend(vector, pc);
    
    ASSERT_THAT(!flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_When_Block_Size_Zero)
    Vector* vector;
	ADTErr flag;
	
	int *pb, *pf, *pc, *pd, *pe;

	vector = VectorCreate(3, 0);

    pb = malloc(sizeof(int));
    pc = malloc(sizeof(int));
    pd = malloc(sizeof(int));
    pe = malloc(sizeof(int));
    pf = malloc(sizeof(int));
    
    *pb = 6;
    *pc = 8;
    *pd = 7;
    *pe = 2;
    *pf = 5;
    
    flag = VectorAppend(vector, pb);
    flag = VectorAppend(vector, pc);
    flag = VectorAppend(vector, pd);	
    flag = VectorAppend(vector, pe);
    flag = VectorAppend(vector, pf);
    ASSERT_THAT(flag == ERR_OVERFLOW);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_And_Remove_Normal_Char)
    Vector* vector;
	ADTErr flag;
	
	char c = 'g', d = 'f';
	char* p = &c, *p2 = &d;
	void *p3;	
	
	vector = VectorCreate(5, 3);
	VectorAppend(vector, p2);
	VectorAppend(vector, p);
	
	flag = VectorRemove(vector, &p3);
	ASSERT_THAT(flag == ERR_OK);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_And_Get_Normal_Char)
    Vector* vector;
	ADTErr flag;
	
	char c = 'g', d = 'f';
	char* p = &c, *p2 = &d;
	void *p3;	
	
	vector = VectorCreate(5, 3);
	VectorAppend(vector, p2);
	VectorAppend(vector, p);
	
	flag = VectorGet(vector, 1, &p3);
	
	ASSERT_THAT(flag == ERR_OK);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Add_And_Set_Normal_Char)
    Vector* vector;
	ADTErr flag;
	
	char c = 'g', d = 'f';
	char* p = &c, *p2 = &d;
	void *p3 = NULL;	
	
	vector = VectorCreate(5, 3);
	VectorAppend(vector, p2);
	VectorAppend(vector, p);
	
	flag = VectorSet(vector, 2, p3);
	
	ASSERT_THAT(flag == ERR_OK);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Num_Of_Items_Array_Null)
    Vector* vector = NULL;
	size_t numOfItems;
	
	numOfItems = VectorSize(vector);
	
	ASSERT_THAT(0 == numOfItems);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Num_Of_Items_After_Creation)
    Vector* vector = NULL;
	size_t numOfItems;
	
	vector = VectorCreate(5, 3);
	numOfItems = VectorSize(vector);
	
	ASSERT_THAT(0 == numOfItems);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Num_Of_Items_After_Adding)
    Vector* vector;
	size_t numOfItems;
	int *pb, *pc;
	int a, b;

    pb = malloc(sizeof(int));
    pc = malloc(sizeof(int));

    a = 2;
    b = 34;

    pb = &a;
    pc = &b;

	vector = VectorCreate(5, 3);
    
    VectorAppend(vector, pb);
    VectorAppend(vector, pc);
	
	numOfItems = VectorSize(vector);
	
	ASSERT_THAT(2 == numOfItems);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Get_Outside_Range)
    Vector* vector;
	ADTErr flag;
	
	char c = 'g', d = 'f';
	char* p = &c, *p2 = &d;
	void *p3;	
	
	vector = VectorCreate(5, 3);
	VectorAppend(vector, p2);
	VectorAppend(vector, p);
	
	flag = VectorGet(vector, 7, &p3);
	
	ASSERT_THAT(ERR_WRONG_INDEX == flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Get_With_Null_Output_Var)
    Vector* vector;
	ADTErr flag;
	
	char c = 'g', d = 'f';
	char* p = &c, *p2 = &d;
	void *p3 = NULL;	
	
	vector = VectorCreate(5, 3);
	VectorAppend(vector, p2);
	VectorAppend(vector, p);
	
	flag = VectorGet(vector, 1, &p3);
	
	ASSERT_THAT(ERR_OK == flag);
	VectorDestroy(&vector, NULL);
END_UNIT
	
UNIT(Test_Get_Array_Null)
    Vector* vector = NULL;
	ADTErr flag;

	void *p3 = NULL;	
	
	flag = VectorGet(vector, 1, &p3);
	
	ASSERT_THAT(ERR_NOT_INITIALIZED == flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Remove_With_Shrink_And_Extention)
	Vector* vector;
	ADTErr flag;
	size_t cap;
	
	int *pb, *pf, *pc, *pd, *pe, *pg, *ph, *pi;
	void *p3;
	int a, b, c, d, e, f, g, h;
	vector = VectorCreate(3, 2);

    pb = malloc(sizeof(int));
    pc = malloc(sizeof(int));
    pd = malloc(sizeof(int));
    pe = malloc(sizeof(int));
    pf = malloc(sizeof(int));
    pg = malloc(sizeof(int));
    ph = malloc(sizeof(int));
    pi = malloc(sizeof(int));
        
    a = 2;
    b = 34;
    c = 32;
    d = 5;
    e = 73;
    f = 32;
    g = 345;
    h = 27;
    
    pb = &a;
    pc = &b;
    pd = &c;
    pe = &d;
    pf = &e;
    pg = &f;
    ph = &g;
    pi = &h;
    
    VectorAppend(vector, pb);
    VectorAppend(vector, pc);
    VectorAppend(vector, pd);	
    VectorAppend(vector, pe);
    VectorAppend(vector, pf);
    VectorAppend(vector, pg);	
    VectorAppend(vector, ph);
    VectorAppend(vector, pi);
    
    VectorRemove(vector, &p3);
    VectorRemove(vector, &p3);
    VectorRemove(vector, &p3);
    VectorRemove(vector, &p3);
    VectorRemove(vector, &p3);
    VectorRemove(vector, &p3);
    VectorRemove(vector, &p3);
	flag = VectorRemove(vector, &p3);
    cap = VectorCapacity(vector);
    
    ASSERT_THAT(ERR_OK == flag && 3 == cap);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Remove_Under_Init_Size)
    Vector* vector;
	ADTErr flag;
	
	char c = 'g', d = 'f';
	char* p = &c, *p2 = &d;
	void *p3;	
	
	vector = VectorCreate(5, 3);
	VectorAppend(vector, p2);
	VectorAppend(vector, p);
	
	VectorRemove(vector, &p3);
	VectorRemove(vector, &p3);
	flag = VectorRemove(vector, &p3);
	ASSERT_THAT(ERR_UNDERFLOW == flag);
	VectorDestroy(&vector, NULL);
END_UNIT

UNIT(Test_Remove_Vector_Null)
    Vector* vector;
	ADTErr flag;
	void *p3;	
	
	vector = NULL;

	flag = VectorRemove(vector, &p3);
	
	ASSERT_THAT(ERR_NOT_INITIALIZED == flag);
	VectorDestroy(&vector, NULL);
END_UNIT

TEST_SUITE(framework test)
	TEST(Create_Normal)
    TEST(Test_Create_Zero_Init)
    TEST(Test_Create_Zero_Extend)
    TEST(Test_Create_Zero_Init_And_Extend)
    TEST(Test_Add_Normal_Int)
    TEST(Test_Add_Normal_Char)
    TEST(Test_Add_Normal_Str)
    TEST(Test_Add_To_Init_Size_Zero)
    TEST(Test_Add_And_Extend)
    TEST(Test_Add_When_Block_Size_Zero)
    TEST(Test_Add_And_Remove_Normal_Char)
    TEST(Test_Add_And_Get_Normal_Char)
    TEST(Test_Add_And_Set_Normal_Char)
    TEST(Test_Num_Of_Items_Array_Null)
    TEST(Test_Num_Of_Items_After_Creation)
    TEST(Test_Num_Of_Items_After_Adding)
    TEST(Test_Get_Outside_Range)
    TEST(Test_Get_With_Null_Output_Var)
    TEST(Test_Get_Array_Null)
    TEST(Test_Remove_With_Shrink_And_Extention)
    TEST(Test_Remove_Under_Init_Size)
    TEST(Test_Remove_Vector_Null)
END_SUITE


