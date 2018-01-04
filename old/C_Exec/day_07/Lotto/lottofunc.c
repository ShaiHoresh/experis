#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Printcard(){

	int lucky[6];
	int i, j, numOfNum = 6;
	char card[6][11]; 
	
	srand(time(NULL));
	
	for(i = 0; i < 6; ++i){
		lucky[i] = rand() % 49 + 1;
		for(j = 0; j < i; ++j){
			if(lucky[i] == lucky[j]) --i;
		}
	}

	for(i = 0; i < 6; ++i){
		for(j = 1; j < 11; ++j){
			card[i][j] = '-';
		}
	}
	card[4][10] = 32;
	for(i = 0; i < numOfNum; ++i){
		card[lucky[i]/10][lucky[i]%10] = '+';  //10's are not in card
		if(lucky[i]%10 == 0){
			card[lucky[i]/10 - 1][10] = '+';
		}
	}
	
	printf("\n  1 2 3 4 5 6 7 8 9 10\n");
	
	for(i = 0; i < 5; ++i){
		printf("%d", i);
		for(j = 1; j < 11; ++j){
			printf(" %c", card[i][j]);
		}
		printf("\n");
	}
}
