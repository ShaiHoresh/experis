#include <stdio.h>
#include <stdlib.h>
#include "DynArray.h"

void main(){

	int i, N,ins;
	intptr numptr;
	unsigned int capacity;
	dynarray* DA;
	
//	printf("Please enter the array length\n");	/*defining array size*/
//	scanf("%d", &capacity);
	capacity = 4;
	
	DA = createDA(capacity);
	if(DA==NULL){
		printf("Memory problem!!\n");
		exit;
	}
	DA->NOE = 0;
	while(N!=-1){								/*insert num to array*/
		
		printf("please enter a number\n");		
		numptr = malloc(sizeof(int));
		if(numptr==NULL){
			printf("memory problem\n");
			break;
		}
		scanf("%d", &N);
		if(N==-1)	break;
		*numptr = N;
		ins=insert(DA, numptr);
		if(ins==0){
			printf("memory problem\n");
			break;
		}
	}

	printf("DA->NOE = %d\n", DA->NOE);
	for(i=0; i<DA->NOE; ++i){
		printf("%d ", *(DA->array[i]));
	}
	printf("\n");
	destroy(DA);
	
}

