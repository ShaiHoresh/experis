#include <stdio.h>
#include <stdlib.h>
#include "Interactive.h"

int main()
{
	int cont = 1;			// trigger to stop loop	
	unsigned int option;
	int capacity = 4;
	dynarray* DA;
	intptr numPtr, flagPtr;
	int flag, num, index, ins, N, i, val;
		
	DA = createDA(capacity);
	if(&DA==NULL){
		printf("Memory problem!!\n");
		return -1;
	}
/*	while(N!=-1){								//insert num to array
		
		printf("please enter a number\n");		
		numPtr = malloc(sizeof(int));
		if(numPtr==NULL){
			printf("memory problem\n");
			break;
		}
		scanf("%d", &N);
		if(N==-1)	break;
		*numPtr = N;
		ins=insert(DA, numPtr);
		if(ins==0){
			printf("memory problem\n");
			break;
		}
	}					*/

	while (cont) {
		printf("Choose option: \n");
		printf("1: Insert  \n");
		printf("2: Find    \n");
		printf("3: Remove  \n");
		printf("4: Print  \n");
		printf("Any another number - stop \n");

		scanf("%d", &option);
		switch (option) {
			case 1:
				printf("Enter the number you want to insert: ");
				scanf("%d", &val);
				printf("Where do you want to put it? ");
				scanf("%d", &index);
				numPtr = malloc(sizeof(int));
				*numPtr = val;
				flag = InsertToIndex(DA, numPtr,index);
//				printf("flag = %d\n", flag);
				if(flag == -1){
					printf("there is a problem. Sorry\n\n");
				} else{
					printf("\n\n");
				}
			break;
			case 2:
				printf("what number are you looking for?\n");
				scanf("%d", &num);
				flagPtr = Find(DA, num);
				if(flagPtr != NULL){
					printf("number found\n");
				} else{
					printf("number doesn't exist in array\n\n");
				}
			break;
			case 3:
				printf("which number do you want to remove?\n");
				scanf("%d", &num);
				flag = Remove(DA, num);	
				if(flag == 0){
					printf("the number doesn't exist in array. Sorry\n\n");
				}				
			break;
			case 4:
/*				if(DA -> NOE > 0){
					printf("Here is your array: ");
					for(i=0; i< (DA -> NOE); ++i){
						printf("%d ", *(DA->array[i]));
					}
					printf("\n\n");
				} else {
					printf("you have an empty array\n\n");
				}					*/
				Print(DA);
			break;
			default: cont = 0;									break;
		}
	}
	destroy(DA);
	return 0;
}

