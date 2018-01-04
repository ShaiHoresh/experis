#include <stdlib.h>
#include "DynArray.h"

int insert(dynarray* DA, intptr N){

	ipp tmp = DA -> array;
	
//	if(N == -1) return 0;
//		(DA->NOE)++;
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

dynarray* createDA(int capacity){
	dynarray* DA = malloc(sizeof(dynarray));
	ipp temp = malloc(capacity*sizeof(intptr));
	if(temp == NULL){
		return 0; 	
	} else{
		DA->NOE=0;
		DA->capacity = capacity;	
		DA->array=temp;
		return DA;
	}
}

void destroy(dynarray* DA){
	int i;
	for(i=0; i<DA->NOE;++i){
		free(DA->array[i]);
	}
	free(DA->array);
	free(DA);
}

//DA->array == NULL ||
