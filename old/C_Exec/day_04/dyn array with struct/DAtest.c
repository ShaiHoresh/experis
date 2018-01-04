#include <stdio.h>
#include "DynArray.h"

void main(){

	int N=0, i;
	unsigned int capacity;
	dynarray* DA;
	
	printf("Please enter the array length\n");	/*defining array size*/
	scanf("%d", &capacity);
	
	DA = createDA(capacity);

	while(N!=-1){								/*insert num to array*/
		printf("please enter a number\n");		
		scanf("%d", &N);
		insert(DA, N);
	}

	for(i=0; i<DA->NOE; ++i){
		printf("%d ", DA->array[i]);
	}
	printf("\n");
	destroy(DA);
	
}
