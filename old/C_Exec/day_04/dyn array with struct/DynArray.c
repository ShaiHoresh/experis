#include <stdlib.h>
#include "DynArray.h"

int insert(dynarray* DA, int N){

	int *tmp1, *tmp2;
	tmp2 = DA -> array;
	if(N == -1) return 0;

	if(DA -> NOE == DA -> capacity){			/*if nessasary - realloc*/
		tmp1 = DA->array;						/*and save the current address*/
		tmp2 = realloc(DA -> array, (DA -> capacity + EXVAL)*sizeof(int));
		DA -> capacity += EXVAL;				/*enlarge capacity value*/
	}
	if(tmp2 == NULL){
//		printf("Not enough memory\n");
//		DA -> array = tmp1;
		return 0; 	
	} else {
		DA -> array[DA->NOE] = N;				/*put the value the user typed*/
		++(DA->NOE);							
//		DA -> capacity += EXVAL;
		return 1;
	}
}

dynarray* createDA(int capacity){
	dynarray* DA;
	DA = malloc(sizeof(dynarray));
	DA->array = malloc(capacity*sizeof(int));
	if(DA->array == NULL || DA == NULL){
		return 0; 	
	}
	DA->NOE=0;
	DA->capacity = capacity;	
	return DA;
}

void destroy(dynarray* DA){
	free(DA);
	free(DA->array);
}
