#include <stdio.h>
#include <stdlib.h>
#define EXVAL 4

int *insert(int *array, int N, int *index, int* capacity);

void main(){

	int* array;
	int size=0, N=0, i=0, index=0;
	printf("Please enter the array length\n");
	scanf("%d", &size);
	array = malloc(size*sizeof(int));
	if(array == NULL){
		printf("Not enough memory\n");
		exit(1); 	
	}
	
/*	if(size <= 0){
		printf("num of cells in array must be posotive\n");
	}									*/

	while(N!=-1){
		printf("please enter a number\n");
		scanf("%d", &N);
		array = insert(array, N, &index, &size);
	}
	
	for(i=0; i<size; ++i){
		printf("%d ", array[i]);
	}
	
	free(array);
	
}

int *insert(int *array, int N, int *index, int* capacity){

	int *tmp1, *tmp2;
	tmp2=array;
	if(N == -1) return array;

	if(*index == *capacity){
		tmp1 = array;
		tmp2 = realloc(array, (*capacity + EXVAL)*sizeof(int));
		*capacity += EXVAL;
	}
	if(tmp2==NULL){
		printf("Not enough memory\n");
		return tmp1; 	
	} else {
		array[*index] = N;
		++(*index);
//		*capacity += EXVAL;
		return tmp2;
	}


}
