#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lotto.h"

int Printcard(int randNumArray[], unsigned int num){

	int i, j, numOfNum = NUM;
	char card[5][11]; 

	for(i = 0; i < 5; ++i){
		for(j = 0; j < 11; ++j){
			card[i][j] = '-';
		}
	}
	for(i = 0; i < 6; ++i){
		printf("%d ",randNumArray[i]);
	}
	printf("\n\n");
	card[4][9] = 32;
	for(i = 0; i < numOfNum; ++i){
		card[(randNumArray[i] - 1)/10][(randNumArray[i] - 1)%10] = '+';
		printf("%d %d\n", (randNumArray[i] - 1)/10, (randNumArray[i] - 1)%10);
	}
	
	printf("\n  1 2 3 4 5 6 7 8 9 10\n");
	
	for(i = 0; i < 5; ++i){
		printf("%d", i);
		for(j = 0; j < 10; ++j){
			printf(" %c", card[i][j]);
		}
		printf("\n");
	}

	return 1;
}

int* randNum(int randNumArray[], unsigned int num){
	
	int i, j;
	int* randPtr;
	srand(time(NULL));
	
	for(i = 0; i < 6; ++i){
		randNumArray[i] = rand() % RANGE + 1;
//		printf("%d ",randNumArray[i]);
		for(j = 0; j < i; ++j){
			if(randNumArray[i] == randNumArray[j]){
				--i;
				break;
			}
		}
	}
	
	for(i = 0; i < 6; ++i){
		printf("%d ",randNumArray[i]);
	}
	printf("\n");
	randPtr = randNumArray;
	return randPtr;
}
