#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void TestCreateNormal();
void TestCreateWInitSizeZero();
void TestCreateWBlockSizeZero();
void TestCreateBlockAndInitZero();
void TestDestroyArrayNull();
void TestAddNormal();
void TestAddVectorNull();
void TestAddIfInitZero();
void TestAddAndResize();
void TestAddWhenBlockSizeZero();
void TestNumOfItemsArrayNull();
void TestNumOfItemsAfterCreation();
void TestNumOfItemsAfterAdding();
void TestGetNormal();	
void TestGetOutsideRange();
void TestGetWNullOutputVar();
void TestGetArrayNull();
void TestSetNormal();	
void TestSetOutsideRange();
void TestSetVectorNull();
void TestDeleteNormal();
void TestDeleteWOVar();
void TestDeleteWShrinkExtention();
void TestDeleteUnderInitSize();
void TestDeleteIfArrayIsEmpty();
void TestDeleteVectorNull();
void TestDeleteAndAddInLoop();
void TestNumOfItemsAfterDeleting();
/****************************************************************************/
int main()
{
	TestCreateNormal();
	TestCreateWInitSizeZero();
	TestCreateWBlockSizeZero();
	TestCreateBlockAndInitZero();
	TestDestroyArrayNull();
	TestAddNormal();
	TestAddVectorNull();
	TestAddIfInitZero();
	TestAddAndResize();
	TestAddWhenBlockSizeZero();
	TestNumOfItemsArrayNull();
	TestNumOfItemsAfterCreation();
	TestNumOfItemsAfterAdding();
	TestGetNormal();
	TestGetOutsideRange();
	TestGetWNullOutputVar();
	TestGetArrayNull();
	TestSetNormal();
	TestSetOutsideRange();
	TestSetVectorNull();
	TestDeleteNormal();
	TestDeleteWOVar();
	TestDeleteWShrinkExtention();
	TestDeleteUnderInitSize();
	TestDeleteIfArrayIsEmpty();
	TestDeleteVectorNull();
	TestDeleteAndAddInLoop();
	TestNumOfItemsAfterDeleting();
	
	return 0;
}
/***************************************************************************/
void TestCreateNormal()
{
	Vector* vector;
	
	vector = VectorCreate(5, 3);
	if(NULL == vector){
		printf("FAILED: Test Create Normal\n");
	}
	else 
	{
		printf("SUCCEEDED: Test Create Normal\n");
	}
	VectorDestroy(vector);
}
/***************************************************************************/
void TestCreateWInitSizeZero()
{
	Vector* vector;
	
	vector = VectorCreate(0, 3);
	if(NULL == vector){
		printf("FAILED: Test create with Initial size of 0\n");
	}
	else 
	{
		printf("SUCCEEDED: Test create with Initial size of 0\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/

void TestCreateWBlockSizeZero()
{
	Vector* vector;
	
	vector = VectorCreate(5, 0);
	if(NULL == vector){
		printf("FAILED: Test create with block size of 0\n");
	}
	else 
	{
		printf("SUCCEEDED: Test create with block size of 0\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/

void TestCreateBlockAndInitZero()
{
	Vector* vector;
	
	vector = VectorCreate(0, 0);
	if(NULL != vector){
		printf("FAILED: Test create with init and block size of 0\n");
	}
	else 
	{
		printf("SUCCEEDED: Test create with init and block size of 0\n");
	}
	VectorDestroy(vector);
}
/***************************************************************************/

void TestDestroyArrayNull()
{
	Vector* vector = NULL;
	
	VectorDestroy(vector);
	printf("SUCCEEDED: Test Destroy NULL array\n");	
}
/***************************************************************************/

/*
void TestDestroyVectorNull(); */
/***************************************************************************/
void TestAddNormal()
{
	Vector* vector;
	ADTErr flag;
	
	vector = VectorCreate(5, 3);
	flag = VectorAdd(vector, 5);
	if(0 == flag)
	{
		printf("SUCCEEDED: Test add to normal vector\n");
	}
	else
	{
		printf("FAILED: Test add to normal vector\n");
	}
	VectorDestroy(vector);
}
/***************************************************************************/

void TestAddVectorNull()
{
	Vector* vector = NULL;
	ADTErr flag;
	
	flag = VectorAdd(vector, 5);
	if(0 != flag)
	{
		printf("SUCCEEDED: Test add to NULL vector\n");
	}
	else
	{
		printf("FAILED: Test add to NULL vector\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
/*void TestAddArrayNull()
{
	Vector* vector;
	ADTErr flag;
	
	vector = VectorCreate(5, 3);
	flag = VectorAdd(vector, 5);
	if(0 != flag)
	{
		printf("SUCCEEDED: Test add to NULL vector\n");
	}
	else
	{
		printf("FAILED: Test add to NULL vector\n");
	}
}																	*/

/***************************************************************************/
void TestAddIfInitZero()
{
	Vector* vector;
	ADTErr flag;
	
	vector = VectorCreate(0, 3);
	flag = VectorAdd(vector, 5);
	if(0 == flag)
	{
		printf("SUCCEEDED: Test add to vector with initial size 0\n");
	}
	else
	{
		printf("FAILED: Test add to vector with initial size 0\n");
	}
	VectorDestroy(vector);
}	

/***************************************************************************/
void TestAddAndResize()
{
	Vector* vector;
	ADTErr flag;
	int i;
	
	vector = VectorCreate(4, 2);

	for(i = 0; i < 8; ++i)
	{
		flag = VectorAdd(vector, i);
		if(0 != flag)
		{
			break;
		}
	}
	if(0 == flag)
	{
		printf("SUCCEEDED: Test add to vector and realloc\n");
	}
	else
	{
		printf("FAILED: Test add to vector and realloc\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
void TestAddWhenBlockSizeZero()
{
	Vector* vector;
	ADTErr flag;
	int i;
	
	vector = VectorCreate(4, 0);

	for(i = 0; i < 8; ++i)
	{
		flag = VectorAdd(vector, i);
		if(0 != flag)
		{
			break;
		}
	}
	if(0 != flag)
	{
		printf("SUCCEEDED: Test try to add to vector with blockSize = 0\n");
	}
	else
	{
		printf("FAILED: Test try to add to vector with blockSize = 0\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
void TestNumOfItemsArrayNull()
{
	Vector* vector = NULL;
	ADTErr flag;
	int numOfItems;
	
	flag = VectorItemsNum(vector, &numOfItems);
	if(0 != flag)
	{
		printf("SUCCEEDED: Test Num of items when array NULL\n");
	}
	else
	{
		printf("FAILED: Test Num of items when array NULL\n");
	}
}

/***************************************************************************/

void TestNumOfItemsAfterCreation()
{
	Vector* vector;
	ADTErr flag;
	int numOfItems;
	
	vector = VectorCreate(4, 2);
	flag = VectorItemsNum(vector, &numOfItems);
	if(0 == flag)
	{
		printf("SUCCEEDED: Test Num of items after creation\n");
	}
	else
	{
		printf("FAILED: Test Num of items after creation\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
void TestNumOfItemsAfterAdding()
{
	Vector* vector;
	ADTErr flag;
	int numOfItems;
	
	vector = VectorCreate(4, 2);
	VectorAdd(vector, 5);
	flag = VectorItemsNum(vector, &numOfItems);
	
	if(0 == flag && numOfItems == 1)
	{
		printf("SUCCEEDED: Test Num of items after adding\n");
	}
	else
	{
		printf("FAILED: Test Num of items after adding\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
void TestGetNormal()
{
	Vector* vector;
	ADTErr zeroFlag, midFlag, maxFlag;
	int i, zero, mid, max;
	
	vector = VectorCreate(4, 2);
	for(i = 0; i < 4; ++i)
	{
		VectorAdd(vector, i);
	}
	zeroFlag = VectorGet(vector, 0, &zero);
	midFlag = VectorGet(vector, 2, &mid);
	maxFlag = VectorGet(vector, 3, &max);
	if(0 == zeroFlag && zero == 0 && midFlag == 0 && mid == 2 && maxFlag == 0 && max == 3)
	{
		printf("SUCCEEDED: Test get normal\n");
	}
	else
	{
		printf("FAILED: Testget normal\n");
	}	
	VectorDestroy(vector);
}

/***************************************************************************/	
void TestGetOutsideRange()
{
	Vector* vector;
	ADTErr flagPos, flagNeg;
	int item;
	
	vector = VectorCreate(4, 2);
	VectorAdd(vector, 5);
	flagPos = VectorGet(vector, 5, &item);
	flagNeg = VectorGet(vector, -5, &item);
	if(0 != flagPos && 0 != flagNeg)
	{
		printf("SUCCEEDED: Test get Outside Range\n");
	}
	else
	{
		printf("FAILED: Test get Outside Range\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
void TestGetWNullOutputVar()
{
	Vector* vector;
	ADTErr flag;
	int* item = NULL;
	
	vector = VectorCreate(4, 2);
	VectorAdd(vector, 5);
	flag = VectorGet(vector, 0, item);

	if(0 != flag)
	{
		printf("SUCCEEDED: Test get with NULL output variant\n");
	}
	else
	{
		printf("FAILED: Test get with NULL output variant\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
void TestGetArrayNull()
{
	Vector* vector = NULL;
	ADTErr flag;
	int item;
	
	flag = VectorGet(vector, 0, &item);

	if(0 != flag)
	{
		printf("SUCCEEDED: Test get with NULL array\n");
	}
	else
	{
		printf("FAILED: Test get with NULLarray\n");
	}
	VectorDestroy(vector);
}

/***************************************************************************/
void TestSetNormal()
{
	Vector* vector;
	ADTErr flag;
	int i;
	
	vector = VectorCreate(4, 2);

	for(i = 0; i < 4; ++i)
	{
		VectorAdd(vector, i);
	}
	
	flag = VectorSet(vector, 2, 88);
	if(0 == flag)
	{
		printf("SUCCEEDED: Test set normal\n");
	}
	else
	{
		printf("FAILED: Test set normal\n");
	}
	VectorDestroy(vector);	
}

/***************************************************************************/
void TestSetOutsideRange()
{
	Vector* vector;
	ADTErr bigFlag, negFlag;
	int i;
	
	vector = VectorCreate(4, 2);

	for(i = 0; i < 4; ++i)
	{
		VectorAdd(vector, i);
	}
	
	bigFlag = VectorSet(vector, 8, 88);
	negFlag = VectorSet(vector, -8, 88);
	if(0 != bigFlag && 0 != negFlag)
	{
		printf("SUCCEEDED: Test set outside range\n");
	}
	else
	{
		printf("FAILED: Test set outside range\n");
	}
	VectorDestroy(vector);	

}

/***************************************************************************/
void TestSetVectorNull()
{
	Vector* vector = NULL;
	ADTErr flag;
	
	flag = VectorSet(vector, 0, 88);
	if(0 != flag)
	{
		printf("SUCCEEDED: Test set Vector NULL\n");
	}
	else
	{
		printf("FAILED: Test set Vector NULL\n");
	}
	VectorDestroy(vector);	
}

/***************************************************************************/
void TestDeleteNormal()
{
	Vector* vector;
	ADTErr flag;
	int i, temp;
	
	vector = VectorCreate(4, 2);

	for(i = 0; i < 4; ++i)
	{
		VectorAdd(vector, i);
	}
	flag = VectorDelete(vector, &temp);
	if(0 == flag && temp == 3)
	{
		printf("SUCCEEDED: Test delete normal\n");
	}
	else
	{
		printf("FAILED: Test delete normal\n");
	}	
	VectorDestroy(vector);
}

/***************************************************************************/
void TestDeleteWOVar()
{
	Vector* vector;
	ADTErr flag;
	int i;
	int* temp = NULL;
	
	vector = VectorCreate(4, 2);

	for(i = 0; i < 4; ++i)
	{
		VectorAdd(vector, i);
	}
	flag = VectorDelete(vector, temp);
	if(0 != flag)
	{
		printf("SUCCEEDED: Test delete with NULL output variant\n");
	}
	else
	{
		printf("FAILED: Test delete with NULL output variant\n");
	}	
	VectorDestroy(vector);
}

/***************************************************************************/
void TestDeleteWShrinkExtention()
{
	Vector* vector;
	ADTErr delFlag, numFlag;
	int i, temp, numOfItems;
	
	vector = VectorCreate(4, 2);

	for(i = 0; i < 10; ++i)
	{
		VectorAdd(vector, i);
	}
	for(i = 0; i < 5; ++i)
	{
		delFlag = VectorDelete(vector, &temp);
	}
	numFlag = VectorItemsNum(vector, &numOfItems);
	if(0 == delFlag && temp == 5 && numFlag == 0 && numOfItems ==5)
	{
		printf("SUCCEEDED: Test delete with shrink extention\n");
	}
	else
	{
		printf("FAILED: Test delete with shrink extention\n");
	}	
	VectorDestroy(vector);
}

/***************************************************************************/
void TestDeleteUnderInitSize()
{
	Vector* vector;
	ADTErr delFlag, numFlag;
	int i, temp, numOfItems;
	
	vector = VectorCreate(4, 2);

	for(i = 0; i < 10; ++i)
	{
		VectorAdd(vector, i);
	}
	for(i = 0; i < 8; ++i)
	{
		delFlag = VectorDelete(vector, &temp);
	}
	numFlag = VectorItemsNum(vector, &numOfItems);
	if(0 == delFlag && temp == 2 && numFlag == 0 && numOfItems == 2)
	{
		printf("SUCCEEDED: Test delete with shrink extention lower than init\n");
	}
	else
	{
		printf("FAILED: Test delete with shrink extention lower than init\n");
	}	
	VectorDestroy(vector);
}

/***************************************************************************/
void TestDeleteIfArrayIsEmpty()
{
	Vector* vector;
	ADTErr delFlag;
	int temp;
	
	vector = VectorCreate(4, 2);
	delFlag = VectorDelete(vector, &temp);
	if(0 != delFlag)
	{
		printf("SUCCEEDED: Test delete empty array\n");
	}
	else
	{
		printf("FAILED: Test delete empty array\n");
	}	
	VectorDestroy(vector);	
}

/***************************************************************************/
void TestDeleteVectorNull()
{
	Vector* vector = NULL;
	ADTErr delFlag;
	int temp;
	
	delFlag = VectorDelete(vector, &temp);
	if(0 != delFlag)
	{
		printf("SUCCEEDED: Test delete NULL array\n");
	}
	else
	{
		printf("FAILED: Test delete NULL array\n");
	}	
	VectorDestroy(vector);	
}

/***************************************************************************/
void TestDeleteAndAddInLoop()
{
	Vector* vector;	
	int i, j, temp;
	ADTErr delFlag;
	
	vector = VectorCreate(4, 2);
	
	for(j = 0; j < 3; ++j)
	{
		for(i = 0; i < 10; ++i)
		{
			VectorAdd(vector, i);
		}
		for(i = 0; i < 8; ++i)
		{
			VectorDelete(vector, &temp);
		}
	}
	delFlag = VectorDelete(vector, &temp);
	if(0 == delFlag)
	{
		printf("SUCCEEDED: Test delete and add in loop\n");
	}
	else
	{
		printf("FAILED: Test delete and add in loop\n");
	}	
	VectorDestroy(vector);	
}

/***************************************************************************/
void TestNumOfItemsAfterDeleting()
{
	Vector* vector;	
	int i, j, numOfItems;
	ADTErr delFlag;
	
	vector = VectorCreate(4, 2);
	
	for(j = 0; j < 3; ++j)
	{
		for(i = 0; i < 10; ++i)
		{
			VectorAdd(vector, i);
		}
		for(i = 0; i < 8; ++i)
		{
			VectorDelete(vector, &numOfItems);
		}
	}
	delFlag = VectorItemsNum(vector, &numOfItems);
	if(0 == delFlag)
	{
		printf("SUCCEEDED: Test num of items after adding and deleting\n");
	}
	else
	{
		printf("FAILED: Test num of items after adding and deleting\n");
	}	
	VectorDestroy(vector);	
}

