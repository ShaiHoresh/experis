#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int TestCreateAddPrint();
int TestEraseTooMuch(Vector** vector);
int TestReallocDown(Vector** vector);
int TestVectorGet(Vector** vector);
int TestVectorSet(Vector** vector);


int main(){
	Vector* vector;
	
	TestCreateAddPrint(&vector);
	TestEraseTooMuch(&vector);
	TestReallocDown(&vector);
	TestVectorGet(&vector);
	TestVectorSet(&vector);
	
	return 0;

}

/*****************************************************************/
int TestCreateAddPrint(Vector** vector)
{

	*vector = VectorCreate(3, 3);
	printf("Start TestCreateAddPrint\n\n");	
	printf("flag - %d\n", VectorAdd(*vector, 9));
	printf("flag - %d\n", VectorAdd(*vector, 3));
	printf("flag - %d\n", VectorAdd(*vector, 8));
	printf("flag - %d\n", VectorAdd(*vector, 2));
	printf("flag - %d\n", VectorAdd(*vector, 3));
	VectorPrint(*vector);
	VectorDestroy(*vector);
	printf("Finished TestCreateAddPrint\n\n");
	
	return 0;
	
}

/*****************************************************************/
int TestEraseTooMuch(Vector** vector)
{

	int lastNum, i, flag=0;
		
	*vector = VectorCreate(3, 3);

	printf("Start TestEraseTooMuch\n\n");

	printf("flag - %d\n", VectorAdd(*vector, 9));
	printf("flag - %d\n", VectorAdd(*vector, 3));
	printf("flag - %d\n", VectorAdd(*vector, 8));
	printf("flag - %d\n", VectorAdd(*vector, 2));
	printf("flag - %d\n", VectorAdd(*vector, 3));
	VectorPrint(*vector);
	for(i = 0; i < 8; ++i)
	{
		if((flag = VectorDelete(*vector, &lastNum)) == 0)
		{
			printf("%d\nNow the vector contains: ", lastNum);
			VectorPrint(*vector);
		}
		else
		{
			printf("flag!!! - %d\n", flag);
		}
		lastNum = 0;
	}
	VectorPrint(*vector);
	VectorDestroy(*vector);
	printf("Finished TestEraseTooMuch\n\n");
	
	return 0;
	
}

/*****************************************************************/
int TestReallocDown(Vector** vector)
{
	int i, numOfItems, temp;
	*vector = VectorCreate(3, 3);

	printf("Start TestReallocDown\n\n");
	
	for(i = 0; i < 15; ++i)
	{
		VectorAdd(*vector, i);
	}
	VectorPrint(*vector);
	
	for(i = 0; i < 5; ++i)
	{
		VectorDelete(*vector, &temp);
		
	}	
	VectorPrint(*vector);
	
	VectorItemsNum(*vector, &numOfItems);
	printf("numOfItems = %d\n", numOfItems);
	for(i = 0; i < 10; ++i)
	{
		VectorDelete(*vector, &temp);
		
	}	
	VectorPrint(*vector);
	
	VectorItemsNum(*vector, &numOfItems);
	printf("numOfItems = %d\n", numOfItems);
	VectorDestroy(*vector);
	printf("Finished TestReallocDown\n\n");
	
	return 0;
	
}

/*****************************************************************/
int TestVectorGet(Vector** vector)
{

	int i, temp;
	*vector = VectorCreate(3, 3);
	
	printf("Start TestVectorGet\n\n");	
	
	for(i = 0; i < 15; ++i)
	{
		VectorAdd(*vector, i);
	}
	VectorPrint(*vector);
	VectorGet(*vector, 5, &temp);
	printf("%d\n", temp);
	VectorDestroy(*vector);
	printf("Finished TestVectorGet\n\n");

	return 0;

}

/*****************************************************************/
int TestVectorSet(Vector** vector)
{

	int i, flag = 0;
	*vector = VectorCreate(3, 3);

	printf("Start TestVectorSet\n\n");

	for(i = 0; i < 15; ++i)
	{
		VectorAdd(*vector, i);
	}
	VectorPrint(*vector);
	VectorSet(*vector, 5, 7);
	VectorPrint(*vector);

	if((flag = VectorSet(*vector, 25, 7)) == 0)
	{
		VectorPrint(*vector);
	}
	else
	{
		printf("You tried to enter to cell that doesn't exist - flag!!! - %d\n", flag);
	}
	

	VectorDestroy(*vector);
	printf("Finished TestVectorSet\n\n");

	return 0;

}
