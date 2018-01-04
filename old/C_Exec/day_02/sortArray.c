
#include <stdio.h>

void Sort(int array[], int num);
void swap(int* x, int* y);

void main(){
	int size=8;
	int array[size], i;
	
	printf("Please, enter %d numbers:\n", size);
	for(i=0; i<size; ++i){
		scanf("%d", &array[i]);
	}
	printf("\nthe unsorted array is: ");
	for(i=0; i<size; ++i){
		printf("%d ", array[i]);	
	}
	printf("\n");
	Sort(array, size);
	printf("the sorted array is:   ");
	for(i=0; i<size; ++i){
		printf("%d ", array[i]);	
	}
	printf("\n");
}

void Sort(int array[], int num){
	int i, j, flag = 1;
	for(i=1; i<num && flag==1; ++i){
		flag = 0;
		for(j=0; j<num-i; ++j){
			if(array[j]>array[j+1]){
			swap(&array[j], &array[j+1]);
			flag = 1;
			}	
//			printf("%d ", array[j]);
		}
//		printf(" - flag's value is %d big num in set: %d \n",flag, array[j]);
	}
}

void swap(int* x, int* y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
