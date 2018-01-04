#include <stdio.h>
#include <stdlib.h>
#include "Interactive.h"

int insert(dynarray* DA, intptr N){

	ipp tmp = DA -> array;
	if(DA -> NOE == DA -> capacity){
		tmp = realloc(DA -> array, (DA -> capacity + EXVAL)*sizeof(intptr));
		DA -> capacity += EXVAL;
		DA -> array = tmp;
	}
	if(tmp == NULL){
		return 0; 	
	} else {
		DA -> array[DA->NOE] = N;
		(DA->NOE)++;
		return 1;
	}
									
}
/**********************************************************************************/
dynarray* createDA(int capacity){
	ipp temp;
	dynarray* DA = malloc(sizeof(dynarray));
	if(DA != NULL){
	temp = malloc(capacity*sizeof(intptr));
 	}
 	if(temp != NULL){
		DA->NOE=0;
		DA->capacity = capacity;	
		DA->array=temp;
		return DA;
	} else {
		free(DA);
	}
}

/**********************************************************************************/

void destroy(dynarray* DA){
	int i;
	if(DA){
		if(DA->array){
			for(i=0; i<DA->NOE;++i){
				free(DA->array[i]);
			}
			free(DA->array);
		}
		free(DA);
	}
}

/**********************************************************************************/

int InsertToIndex(dynarray* DA, int* numptr, unsigned int index){
	int tmp;
//	printf("I'm here\n");
	if(index > DA->NOE) return -1;
	tmp = shiftRight(DA, index);
	if(tmp==0)	return 0;
	DA -> array[index] = numptr;
	DA -> NOE ++;
//	printf("NOE = %d ", DA -> NOE);
	return 1;
}
/**********************************************************************************/
intptr Find(dynarray* DA, int num){
	int i;
	for(i=0; i<DA->NOE; ++i){
		if(*(DA->array[i])==num)	return DA->array[i];
	}
	return NULL;
}
/**********************************************************************************/
int FindIndex(dynarray* DA, int num){
	int i;
	for(i=0; i<DA->NOE; ++i){
		if(*(DA->array[i])==num){
			printf("index = %d\n", i);
			return i;
		}	
	}
	return -1;
}
/**********************************************************************************/
int Remove(dynarray* DA, int num){
	int index;
	index = FindIndex(DA, num);
	if(index == -1){
		return 0;
	}
	shiftLeft(DA, index);
	DA->NOE--;
	return 1;
}
/**********************************************************************************/

int Print(dynarray* DA){
	int i;
	if(DA -> NOE > 0){
		printf("Here is your array: ");
		for(i=0; i< (DA -> NOE); ++i){
			printf("%d ", *(DA->array[i]));
		}
		printf("\n\n");
	} else {
		printf("you have an empty array\n\n");
	}
}											
/**********************************************************************************/
int shiftLeft(dynarray* DA, unsigned int index){
	int i;
	if(index < 0)			return 0;
//	printf("index = %d\n", index);
	for(i = index; i < (DA -> NOE); ++i){
		DA -> array[i] = DA -> array[i+1];		
	}
	free(DA->array[DA->NOE]);
	return 1;
}
/**********************************************************************************/

int shiftRight(dynarray* DA, unsigned int index){
	int i;
	
	if(index > DA->NOE)		return 0;
	printf("Entered into shiftRight\n");
	ipp tmp = DA -> array;
	if(DA -> NOE >= DA -> capacity){
		tmp = realloc(DA -> array, (DA -> capacity + EXVAL)*sizeof(intptr));
		DA -> capacity += EXVAL;
		DA -> array = tmp;
	}
	if(tmp == NULL){
		return 0; 
	}
	
	for(i=DA->NOE; i>index; --i){
		DA->array[i]=DA->array[i-1];
	}
	return 1;
}

