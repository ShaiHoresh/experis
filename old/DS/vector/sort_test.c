#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdlib.h>
#include "ADTDefs.h"
#include "vector.h"
#include "Sorts.h"


static int SizeArrFunc(Vector* _vec)
{
	int sizearr;
	ADTErr check;
	check = VectorItemsNum(_vec, &sizearr);
	if(ERR_OK != check )
	{
		return -1;
	}
	return (sizearr-1);
}


static int IsSorted(Vector* _vec)
{
	int i = 0;
	int endIndex;
	int first;
	int sec;
	endIndex = SizeArrFunc(_vec);
	if(endIndex < 1)
	{
		return 0;
	}	
	for(i = 0 ; i < endIndex ; ++i)
	{
		VectorGet(_vec, i, &first);
		VectorGet(_vec, i+1, &sec);	
		if(first > sec)
		{
			return 0;
		}	
	}
	return 1;
}

static int IsSortedUpSideDown(Vector* _vec)
{
	int i = 0;
	int endIndex;
	int first;
	int sec;
	endIndex = SizeArrFunc(_vec);
	if(endIndex < 1)
	{
		return 0;
	}	
	for(i = 0 ; i < endIndex ; ++i)
	{
		VectorGet(_vec, i, &first);
		VectorGet(_vec, i+1, &sec);	
		if(first < sec)
		{
			return 0;
		}	
	}
	return 1;
}

/*********************************************************************/

void EmptyVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = BubbleSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: Empty Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	check = BubbleSort(vec);
	if (ERR_NOT_INITIALIZED == check )
	{
		printf("\npass: 1 items Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: 1 items Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void TwoItemsVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );	
	check = BubbleSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: 2 items Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void SmallVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );	
	check = BubbleSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: small Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  6412 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  70 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  62 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );	
	check = BubbleSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: large Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = BubbleSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: sorted Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = BubbleSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void SameValueVectorBubbleSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = BubbleSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector Bubble Sort\n");
	}
	else
	{
		printf("\nfail: Same Value Vector Bubble Sort\n");
	}
	VectorDestroy(vec);
	return;
}
/*******************************************************/
void EmptyVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = ShakeSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: Empty Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	check = ShakeSort(vec);
	if (ERR_NOT_INITIALIZED == check )
	{
		printf("\npass: 1 items Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: 1 items Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void TwoItemsVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );	
	check = ShakeSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: 2 items Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}


void SmallVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );	
	check = ShakeSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: small Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  6412 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  70 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  62 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );	
	check = ShakeSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: large Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = ShakeSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: sorted Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = ShakeSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void SameValueVectorShakeSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = ShakeSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector Shake Sort\n");
	}
	else
	{
		printf("\nfail: Same Value Vector Shake Sort\n");
	}
	VectorDestroy(vec);
	return;
}
/***************************************************************************************/

void EmptyVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = QuickSortRec(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector QuickSortRec\n");
	}
	else
	{
		printf("\nfail: Empty Vector QuickSortRec\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	check = QuickSortRec(vec);
	if (ERR_NOT_INITIALIZED == check )
	{
		printf("\npass: 1 items Vector QuickSortRec\n");
	}
	else
	{
		printf("\nfail: 1 items Vector QuickSortRec\n");
	}
	VectorDestroy(vec);
	return;
}

void TwoItemsVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );	
	check = QuickSortRec(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector QuickSortRec\n");
	}
	else
	{
		printf("\nfail: 2 items Vector QuickSortRec\n");
	}
	VectorDestroy(vec);
	return;
}

void SmallVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );	
	check = QuickSortRec(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector QuickSortRec\n");
	}
	else
	{
		printf("\nfail: small Vector QuickSortRec\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  642 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  711 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  6240);
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );	
	check = QuickSortRec(vec);	
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector QuickSortRec\n");
	}
	else
	{
		printf("\nfail: large Vector QuickSortRec\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = QuickSortRec(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector QuickSortRec\n");
	}
	else
	{
		printf("\nfail: sorted Vector QuickSortRec\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = QuickSortRec(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector QuickSortRec\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector QuickSortRec\n");
	}
	VectorDestroy(vec);
	return;
}

void SameValueVectorQuickSortRec()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = QuickSortRec(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector QuickSort Rec\n");
	}
	else
	{
		printf("\nfail: Same Value Vector QuickSort Rec\n");
	}
	VectorDestroy(vec);
	return;
}
/****************************************************************************/


void EmptyVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = QuickSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: Empty Vector QuickSort\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );	
	check = QuickSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: 1 items Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: 1 items Vector QuickSort\n");
	}
	VectorDestroy(vec);
	return;
}
void TwoItemsVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );	
	check = QuickSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: 2 items Vector QuickSort\n");
	}
	VectorDestroy(vec);
	return;
}
void SmallVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );	
	check = QuickSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: small Vector QuickSort\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  642 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  711 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  6240);
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );	
	check = QuickSort(vec);	
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: large Vector QuickSort\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = QuickSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: sorted Vector QuickSort\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = QuickSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector QuickSort\n");
	}
	VectorDestroy(vec);
	return;
}

void SameValueVectorQuickSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = QuickSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector QuickSort\n");
	}
	else
	{
		printf("\nfail: Same Value Vector QuickSort \n");
	}
	VectorDestroy(vec);
	return;
}
/******************************************************************************************/

void EmptyVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = SelectionSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: Empty Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );	
	check = ShellSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: 1 items Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: 1 items Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void TwoItemsVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  23 );	
	check = SelectionSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: 2 items Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void SmallVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );	
	check = SelectionSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: small Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  642 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  711 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  6240);
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );
	check = SelectionSort(vec);	
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: large Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = SelectionSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: sorted Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = SelectionSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void SameValueVectorSelectionSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = SelectionSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector Selection Sort\n");
	}
	else
	{
		printf("\nfail: Same Value Vector Selection Sort\n");
	}
	VectorDestroy(vec);
	return;
}
/*************************************************/

void EmptyVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = ShellSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: Empty Vector Shell Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );	
	check = ShellSort(vec);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: 1 items Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: 1 items Vector Shell Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void TwoItemsVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  23 );	
	check = ShellSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: 2 items Vector Shell Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void SmallVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	check = ShellSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: small Vector Shell Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  642 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  711 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  6240);
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );	
	check = ShellSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: large Vector Shell Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = ShellSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: sorted Vector Shell Sort\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = ShellSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector Shell Sort\n");
	}
	VectorDestroy(vec);
	return;
}

void SameValueVectorShellSort()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = ShellSort(vec);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector Shell Sort\n");
	}
	else
	{
		printf("\nfail: Same Value Vector Shell Sort \n");
	}
	VectorDestroy(vec);
	return;
}

/*****************************************/
int UpsideDown(int _firstIValue, int _secIValue)
{
	if (_firstIValue >= _secIValue)
	{
		return 0;
	}
	return 1;
}

int DownsideUp(int _firstIValue, int _secIValue)
{
	if (_firstIValue > _secIValue)
	{
		return 1;
	}
	return 0;
}


void EmptyVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = InsertionSort(vec, DownsideUp);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: Empty Vector InsertionSort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );	
	check = InsertionSort(vec, DownsideUp);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: 1 items Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: 1 items Vector Insertion Sort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}
void TwoItemsVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: 2 items Vector Insertion Sort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}
void SmallVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: small Vector Insertion Sort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  642 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  711 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  6240);
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: large Vector Insertion Sort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: sorted Vector Insertion Sort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector Insertion Sort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}

void SameValueVectorInsertionSortDownsideUp()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector Insertion Sort DownsideUp\n");
	}
	else
	{
		printf("\nfail: Same Value Vector Insertion Sort DownsideUp\n");
	}
	VectorDestroy(vec);
	return;
}
/*****************************************************************************/

void EmptyVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	check = InsertionSort(vec, UpsideDown);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: Empty Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: Empty Vector InsertionSort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}

void OneItemsVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );	
	check = InsertionSort(vec, DownsideUp);
	if (ERR_NOT_INITIALIZED == check)
	{
		printf("\npass: 1 items Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: 1 items Vector Insertion Sort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}
void TwoItemsVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: 2 items Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: 2 items Vector Insertion Sort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}
void SmallVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );	
	check = InsertionSort(vec, DownsideUp);
	sort = IsSorted(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: small Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: small Vector Insertion Sort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}
void LongVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  23 );
	VectorAdd  ( vec ,  27 );
	VectorAdd  ( vec ,  64 );
	VectorAdd  ( vec ,  15 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  271 );
	VectorAdd  ( vec ,  642 );
	VectorAdd  ( vec ,  100 );
	VectorAdd  ( vec ,  30 );
	VectorAdd  ( vec ,  711 );
	VectorAdd  ( vec ,  40 );
	VectorAdd  ( vec ,  150 );
	VectorAdd  ( vec ,  50 );
	VectorAdd  ( vec ,  20 );
	VectorAdd  ( vec ,  210 );
	VectorAdd  ( vec ,  6240);
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  11 );	
	check = InsertionSort(vec, UpsideDown);
	sort = IsSortedUpSideDown(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: large Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: large Vector Insertion Sort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}
void SortedVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  10 );	
	check = InsertionSort(vec, UpsideDown);
	sort = IsSortedUpSideDown(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: sorted Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: sorted Vector Insertion Sort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}
void UpSideDownVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  10 );
	VectorAdd  ( vec ,  9 );
	VectorAdd  ( vec ,  8 );
	VectorAdd  ( vec ,  7 );
	VectorAdd  ( vec ,  6 );
	VectorAdd  ( vec ,  5 );
	VectorAdd  ( vec ,  4 );
	VectorAdd  ( vec ,  3 );
	VectorAdd  ( vec ,  2 );
	VectorAdd  ( vec ,  1 );	
	check = InsertionSort(vec, UpsideDown);
	sort = IsSortedUpSideDown(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: UpSideDown Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: UpSideDown Vector Insertion Sort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}

void SameValueVectorInsertionSortUpsideDown()
{
	Vector* vec;
	ADTErr check;
	int sort;
	vec = VectorCreate   ( 10 , 10 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );
	VectorAdd  ( vec ,  1 );	
	check = InsertionSort(vec, UpsideDown);
	sort = IsSortedUpSideDown(vec);
	if (ERR_OK == check && 1 == sort)
	{
		printf("\npass: Same Value Vector Insertion Sort UpsideDown\n");
	}
	else
	{
		printf("\nfail: Same Value Vector Insertion Sort UpsideDown\n");
	}
	VectorDestroy(vec);
	return;
}
/**************************************************/

double compareRunTimeThousend(sortfunc _pick)
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(1000, 100);
	srand(time(NULL));
	for(i = 0; i < 1000 ; ++i)
	{
		VectorAdd  (vec, rand()% 100000);
	}
	timer = clock();
	check = _pick(vec);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSorted(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}

double compareRunTimeInsertionThousend()
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(1000, 100);
	srand(time(NULL));
	for(i = 0; i < 1000 ; ++i)
	{
		VectorAdd  (vec, rand()% 100000);
	}
	timer = clock();
	check = InsertionSort(vec, UpsideDown);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSortedUpSideDown(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}
void compareRunTimeThousendRandomitems()
{
	double res;
	res = compareRunTimeThousend(BubbleSort);
	if (0 == res)
	{
		printf("\n              Bubble sort error\n" );
	}
	else
	{
	printf("\nrun time for Bubble sort with 1,000 random items is %f sec\n", res);
	}
	res = compareRunTimeThousend(ShakeSort);
	if (0 == res)
	{
		printf("\n              Shake Sort error\n" );
	}
	else
	{
	printf("\nrun time for Shake Sort with 1,000 random items is %f sec\n", res);
	}
	res = compareRunTimeInsertionThousend(InsertionSort);
	if (0 == res)
	{
		printf("\n              Insertion error\n" );
	}
	else
	{
	printf("\nrun time for Insertion sort with 1,000 random items is %f sec\n", res);
	}
	res = compareRunTimeThousend(SelectionSort);
	if (0 == res)
	{
		printf("\n              Selection Sort Rec error\n" );
	}
	else
	{
	printf("\nrun time for Selection Sort with 1,000 random items is %f sec\n", res);
	}
		
	res = compareRunTimeThousend(ShellSort);
	if (0 == res)
	{
		printf("\n              Shell Sort error\n" );
	}
	else
	{
	printf("\nrun time for Shell Sort with 1,000 random items is %f sec\n", res);
	}
		
	res = compareRunTimeThousend(QuickSort);
	if (0 == res)
	{
		printf("\n              Quick Sort error\n" );
	}
	else
	{
	printf("\nrun time for Quick Sort with 1,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimeThousend(QuickSortRec);
	if (0 == res)
	{
		printf("\n              Quick Sort Rec error\n" );
	}
	else
	{
	printf("\nrun time for Quick Sort Rec with 1,000 random items is %f sec\n", res);
	}

	

}
/***********************************************************/

double compareRunTimefiftyThousend(sortfunc _pick)
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(50000, 100);
	srand(time(NULL));
	for(i = 0; i < 50000 ; ++i)
	{
		VectorAdd  (vec, rand()% 200000);
	}
	timer = clock();
	check = _pick(vec);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSorted(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}

double compareRunTimeInsertionfiftyThousend()
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(50000, 100);
	srand(time(NULL));
	for(i = 0; i < 50000 ; ++i)
	{
		VectorAdd  (vec, rand()% 200000);
	}
	timer = clock();
	check = InsertionSort(vec, UpsideDown);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSortedUpSideDown(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}

void compareRunTimefiftyThousendRandomitems()
{
	double res;
	res = compareRunTimefiftyThousend(BubbleSort);
	if (0 == res)
	{
		printf("\n              Bubble sort error\n" );
	}
	else
	{
	printf("\nrun time for Bubble sort with 50,000 random items is %f sec\n", res);
	}
	
	
	res = compareRunTimefiftyThousend(ShakeSort);
	if (0 == res)
	{
		printf("\n              Shake Sort error\n" );
	}
	else
	{
	printf("\nrun time for Shake Sort with 50,000 random items is %f sec\n", res);
	}
		
	res = compareRunTimeInsertionfiftyThousend();
	if (0 == res)
	{
		printf("\n              Insertion error\n" );
	}
	else
	{
	printf("\nrun time for Insertion sort with 50,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimefiftyThousend(SelectionSort);
	if (0 == res)
	{
		printf("\n              Selection Sort Rec error\n" );
	}
	else
	{
	printf("\nrun time for Selection Sort with 50,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimefiftyThousend(ShellSort);
	if (0 == res)
	{
		printf("\n              Shell Sort error\n" );
	}
	else
	{
	printf("\nrun time for Shell Sort with 50,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimefiftyThousend(QuickSort);
	if (0 == res)
	{
		printf("\n              Quick Sort error\n" );
	}
	else
	{
	printf("\nrun time for Quick Sort with 50,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimefiftyThousend(QuickSortRec);
	if (0 == res)
	{
		printf("\n              Quick Sort Rec error\n" );
	}
	else
	{
	printf("\nrun time for Quick Sort Rec with 50,000 random items is %f sec\n", res);
	}
}


/******************************************************************************/

double compareRunTimeTenThousend(sortfunc _pick)
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(10000, 100);
	srand(time(NULL));
	for(i = 0; i < 10000 ; ++i)
	{
		VectorAdd  (vec, rand()% 200000);
	}
	timer = clock();
	check = _pick(vec);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSorted(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}

double compareRunTimeInsertionTenThousend()
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(10000, 100);
	srand(time(NULL));
	for(i = 0; i < 10000 ; ++i)
	{
		VectorAdd  (vec, rand()% 200000);
	}
	timer = clock();
	check = InsertionSort(vec, UpsideDown);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSortedUpSideDown(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}

void compareRunTimeTenThousendRandomitems()
{
	double res;
	res = compareRunTimeTenThousend(BubbleSort);
	if (0 == res)
	{
		printf("\n              Bubble sort error\n" );
	}
	else
	{
	printf("\nrun time for Bubble sort with 10,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimeTenThousend(ShakeSort);
	if (0 == res)
	{
		printf("\n              Shake Sort error\n" );
	}
	else
	{
	printf("\nrun time for Shake Sort with 10,000 random items is %f sec\n", res);
	}
		
	res = compareRunTimeInsertionTenThousend();
	if (0 == res)
	{
		printf("\n              Insertion error\n" );
	}
	else
	{
	printf("\nrun time for Insertion sort with 10,000 random items is %f sec\n", res);
	}
	res = compareRunTimeTenThousend(SelectionSort);
	if (0 == res)
	{
		printf("\n              Selection Sort Rec error\n" );
	}
	else
	{
	printf("\nrun time for Selection Sort with 10,000 random items is %f sec\n", res);
	}
	res = compareRunTimeTenThousend(ShellSort);
	if (0 == res)
	{
		printf("\n              Shell Sort error\n" );
	}
	else
	{
	printf("\nrun time for Shell Sort with 10,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimeTenThousend(QuickSort);
	if (0 == res)
	{
		printf("\n              Quick Sort error\n" );
	}
	else
	{
	printf("\nrun time for Quick Sort with 10,000 random items is %f sec\n", res);
	}
	
	res = compareRunTimeTenThousend(QuickSortRec);
	if (0 == res)
	{
		printf("\n              Quick Sort Rec error\n" );
	}
	else
	{
	printf("\nrun time for Quick Sort Rec with 10,000 random items is %f sec\n", res);
	}
}

/*********************************************************************************************/

double Best(sortfunc _pick)
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(10000, 100);
	for(i = 0; i < 50000 ; ++i)
	{
		VectorAdd  (vec, i);
	}
	timer = clock();
	check = _pick(vec);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSorted(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;	
}

double Worst(sortfunc _pick)
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(10000, 100);
	for(i = 50000; i > 0 ; --i)
	{
		VectorAdd  (vec, i);
	}
	timer = clock();
	check = _pick(vec);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSorted(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;	
}

double BestInsertion()
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(10000, 100);
	for(i = 0; i < 50000 ; ++i)
	{
		VectorAdd  (vec, i);
	}
	timer = clock();
	check = InsertionSort(vec, DownsideUp);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSorted(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}

double WorstInsertion()
{
	int i;
	double timeResult;
	int sort;
	clock_t timer;
	Vector* vec;
	ADTErr check;
	vec = VectorCreate(10000, 100);
	for(i = 50000; i > 0 ; --i)
	{
		VectorAdd  (vec, i);
	}
	timer = clock();
	check = InsertionSort(vec, DownsideUp);
	timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	sort = IsSorted(vec);			
	if (ERR_OK == check && 1 == sort)
	{
	}
	else
	{
		timeResult = 0;
	}
	VectorDestroy(vec);
	return timeResult;
}

void compareBW()
{
	double res;
	printf("\n         best-worst time compare : \n\n");
	printf("\n\n          bubble sort : \n");
	res = Best(BubbleSort);
	if (0 == res)
	{
		printf("\n              Bubble sort error\n" );
	}
	else
	{
	printf("\nbest time for Bubble sort 50,000 items is %f sec\n", res);
	}
	
	res = Worst(BubbleSort);
	if (0 == res)
	{
		printf("\n\n              Bubble sort error\n" );
	}
	else
	{
	printf("\nworst time for Bubble sort 50,000 items is %f sec\n", res);
	}
	
	printf("\n\n         shake sort : \n");
	res = Best(ShakeSort);
	if (0 == res)
	{
		printf("\n              shake Sort error\n" );
	}
	else
	{
	printf("\nbest time for shake Sort 50,000 items is %f sec\n", res);
	}
	
	res = Worst(ShakeSort);
	if (0 == res)
	{
		printf("\n              shake Sort error\n" );
	}
	else
	{
	printf("\nworst time for shake Sort 50,000 items is %f sec\n", res);
	}
	
	printf("\n\n         insertion sort : \n");
	res = BestInsertion();
	if (0 == res)
	{
	printf("\n              insertion Sort error\n" );
	}
	else
	{
	printf("\nbest time for insertion Sort 50,000 items is %f sec\n", res);
	}
	
	res = WorstInsertion();
	if (0 == res)
	{
		printf("\n              shake Sort error\n" );
	}
	else
	{
	printf("\nworst time for insertion Sort 50,000 items is %f sec\n", res);
	}
	
	
	printf("\n\n         Quick Sort : \n");	
	res = compareRunTimefiftyThousend(QuickSort);
	if (0 == res)
	{
		printf("\n              Quick Sort error\n" );
	}
	else
	{
	printf("\nbest time for Quick Sort with 50,000 random items is %f sec\n", res);
	}
	res = Best(QuickSort);
	if (0 == res)
	{
		printf("\n\n              Quick sort error\n" );
	}
	else
	{
	printf("\nworst time for Quick sort with 50,000 items is %f sec\n", res);
	}	
		
	printf("\n\n         Quick Sort Rec: \n");	
	res = compareRunTimefiftyThousend(QuickSortRec);
	if (0 == res)
	{
		printf("\n              Quick Sort Rec error\n" );
	}
	else
	{
	printf("\nbest time for Quick Sort Rec with 50,000 random items is %f sec\n", res);
	}
	res = Best(QuickSortRec);
	if (0 == res)
	{
		printf("\n              Quick sort Rec error\n" );
	}
	else
	{
	printf("\nworst time for Quick sort Rec with 50,000 items is %f sec\n", res);
	}		
	
	return;	
	
	
}

/********************************************************************************/
int main()
{
/*
	printf("\n         Bubble Sort: \n");
	EmptyVectorBubbleSort();
	OneItemsVectorBubbleSort();
	TwoItemsVectorBubbleSort();
	SmallVectorBubbleSort();
	LongVectorBubbleSort();
	SortedVectorBubbleSort();
	UpSideDownVectorBubbleSort();
	SameValueVectorBubbleSort();
	
	printf("\n\n         shake Sort: \n");
	EmptyVectorShakeSort();
	OneItemsVectorShakeSort();
	TwoItemsVectorShakeSort();
	SmallVectorShakeSort();
	LongVectorShakeSort();
	SortedVectorShakeSort();
	UpSideDownVectorShakeSort();
	SameValueVectorShakeSort();
	
	printf("\n\n         quick Sort rec: \n");
	EmptyVectorQuickSortRec();
	OneItemsVectorQuickSortRec();
	TwoItemsVectorQuickSortRec();
	SmallVectorQuickSortRec();
	LongVectorQuickSortRec();
	SortedVectorQuickSortRec();
	UpSideDownVectorQuickSortRec();
	SameValueVectorQuickSortRec();
	
	printf("\n\n         quick Sort : \n");
	EmptyVectorQuickSort();
	OneItemsVectorQuickSort();
	TwoItemsVectorQuickSort();
	SmallVectorQuickSort();
	LongVectorQuickSort();
	SortedVectorQuickSort();
	UpSideDownVectorQuickSort();
	SameValueVectorQuickSort();
	
	printf("\n\n        Insertion Sort UpsideDown : \n");
	EmptyVectorInsertionSortUpsideDown();
	OneItemsVectorInsertionSortUpsideDown();
	TwoItemsVectorInsertionSortUpsideDown();
	SmallVectorInsertionSortUpsideDown();
	LongVectorInsertionSortUpsideDown();
	SortedVectorInsertionSortUpsideDown();
	UpSideDownVectorInsertionSortUpsideDown();
	SameValueVectorInsertionSortDownsideUp();
	
	printf("\n\n         Insertion Sort DownsideUp : \n");
	EmptyVectorInsertionSortDownsideUp();
	OneItemsVectorInsertionSortDownsideUp();
	TwoItemsVectorInsertionSortDownsideUp();
	SmallVectorInsertionSortDownsideUp();
	LongVectorInsertionSortDownsideUp();
	SortedVectorInsertionSortDownsideUp();
	UpSideDownVectorInsertionSortDownsideUp();
	SameValueVectorInsertionSortDownsideUp();

	printf("\n\n         Shell Sort : \n");
	EmptyVectorShellSort();
	OneItemsVectorShellSort();
	TwoItemsVectorShellSort();
	SmallVectorShellSort();
	LongVectorShellSort();
	SortedVectorShellSort();
	UpSideDownVectorShellSort();
	SameValueVectorShellSort();

	printf("\n\n         Selection Sort : \n");
	EmptyVectorSelectionSort();
	OneItemsVectorSelectionSort();
	TwoItemsVectorSelectionSort();
	SmallVectorSelectionSort();
	LongVectorSelectionSort();
	SortedVectorSelectionSort();
	UpSideDownVectorSelectionSort();
	SameValueVectorSelectionSort();
*/
	printf("\n");
	printf("\n         time compare 1,000 items : \n");		
	compareRunTimeThousendRandomitems();
	printf("\n         time compare 10,000 items : \n");		
	compareRunTimeTenThousendRandomitems();
	printf("\n         time compare 50,000 items : \n");		
	compareRunTimefiftyThousendRandomitems();
	printf("\n\n");
	
	compareBW();

	printf("\n\n");
	return 0;
}








