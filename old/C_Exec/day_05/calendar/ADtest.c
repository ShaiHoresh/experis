#include <stdio.h>
#include <stdlib.h>
#include "AD.h"

void main(){

	int cont = 1, option, capacity, flag, i;
	ADstruct* newAD = NULL;
	unsigned int room;
	float begin, end;
	meeting* newMeet;
		
	
		while (cont) {
		printf("Choose option:\n");
		printf("1: create AD\n");
		printf("2: create meeting\n");
		printf("3: insert meeting to AD\n");
		printf("4: remove meeting from AD\n");
		printf("5: find meeting in AD\n");
		printf("6: destroy AD\n");
		printf("7: print AD\n");
		printf("8: find meetin pointer\n");
		printf("Any another number - stop \n");

		scanf("%d", &option);
		switch (option) {
			case 1:
//				newAD = malloc(sizeof(DAstruct));
				printf("how many meeting are you willing to have today?\n");
				scanf("%d", &capacity);
				newAD = createAD(capacity);
				if(newAD == NULL){
					printf("Unable to create AD\n");
					cont = 0;
				}
			break;
			case 2:
				printf("insert meeting room num: \n");
				scanf("%d", &room);
				printf("insert meeting start time: \n");
				scanf("%f", &begin);
				printf("insert meeting end time: \n");
				scanf("%f", &end);
				newMeet = CreateMeeting(room, begin, end);
				if(newMeet == NULL){
					printf("didn't succeed to create your meeting\n");
				}
			break;
			case 3:
				flag = insAppToAD(newAD, newMeet);
				if(flag == -1){
					printf("can't enter this meeting to calendar. Sorry )-:\n");
				} else {
					printf("meeting number - %d\n", flag);
				}
			break;
			case 4:
				printf("when the meetng you want to delete starts?\n");
				scanf("%f", &begin);
				flag = removeApp(newAD, begin);
				if(flag == -1){
					printf("you don't have any meeting at %f.\n", begin);
				}
			break;
			case 5:
				printf("when the meeting you want to find starts?\n");
				scanf("%f", &begin);
				flag = find(newAD, begin);
				if(flag == -1){
					printf("you don't have any meeting at %f.\n", begin);
				} else {
					printf("this is your %d meeting today. Good Luck!\n", i+1);
				}
			break;
			case 6:
				printf("Are you sure you want to delete your array?\n0 - NO!!!\n 1 - yes\n");
				scanf("%d", &flag);
				if(flag == 1){
					newAD = destroy(newAD);
				}
			break;
			case 7:
				Print(newAD);
			break;
			case 8:
				if(findPtr(newAD, begin) != NULL){
					printf("I found something\n");
				}
			break;			
			default: cont = 0;
			break;
		}
	}

	if(newAD != NULL){
		destroy(newAD);
	}

}
