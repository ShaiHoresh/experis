	#include <stdio.h>
	#include <stdlib.h>
	#define EXVAL 4

	typedef struct{
		int*	array;
		int		NOE;
		int		capacity;
	}dynarray;

void insert(dynarray* DA, int N);

void main(){

	int N=0, i;
	dynarray DA;
	
	printf("Please enter the array length\n");	/*defining array size*/
	scanf("%d", &DA.capacity);
	DA.array = malloc(DA.capacity*sizeof(int));
	if(DA.array == NULL){
		printf("Not enough memory\n");
		exit(1); 	
	}
	DA.NOE=0;
	

	while(N!=-1){								/*insert num to array*/
		printf("please enter a number\n");		
		scanf("%d", &N);
		insert(&DA, N);
	}

	for(i=0; i<DA.NOE; ++i){
		printf("%d ", DA.array[i]);
	}
	printf("\n");
	free(DA.array);
	
}

void insert(dynarray* DA, int N){

	int *tmp1, *tmp2;
	tmp2 = DA -> array;
	if(N == -1) return;

	if(DA -> NOE == DA -> capacity){			/*if nessasary - realloc*/
		tmp1 = DA->array;						/*and save the current address*/
		tmp2 = realloc(DA -> array, (DA -> capacity + EXVAL)*sizeof(int));
		DA -> capacity += EXVAL;				/*enlarge capacity value*/
	}
	if(tmp2 == NULL){
		printf("Not enough memory\n");
//		DA -> array = tmp1;
		return; 	
	} else {
		DA -> array[DA->NOE] = N;				/*put the value the user typed*/
		++(DA->NOE);							
//		DA -> capacity += EXVAL;
		return;
	}
}
