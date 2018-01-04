#include <stdio.h>
#include <stdlib.h>
#include "AD.h"
/*
ADstruct* ImportCalFromFile(char* _fileName);
int ExportToFile(ADstruct* _AD, char* _fileName);
*/
int main(){

	int cont = 1, option, flag, initCap;
	ADstruct* newAD = NULL;
	unsigned int room;
	float begin, end;
	meetPtr newMeet;
	char fileName[64];
	ADTErr ADTflag;
	
		while (cont) {
		printf("Choose option:\n");
		printf("0: Import a calendar\n");
		printf("1: Create a daily calendar\n");
		printf("2: Create meeting\n");
		printf("3: Insert meeting to AD\n");
		printf("4: Remove meeting from AD\n");
		printf("5: Find meeting in AD\n");
		printf("6: Destroy AD\n");
		printf("7: Print AD\n");
		printf("8: Find meeting pointer\n");
		printf("9: Export to file\n");
		printf("Any another number - stop \n");

		scanf("%d", &option);
		switch (option)
		{
		    case 0:
		        printf("Please insert file name:\n");
		        scanf("%s", fileName);
		        ADTflag = ImportCalFromFile(newAD, fileName);
				if(ADTflag == ERR_OK)
				{
					printf("AD updated\n");
				}
				else
				{
				    printf("Unable to upload AD\n");
				}
	        break;
			case 1:
			    printf("Please insert initial capacity:\n");
			    scanf("%d", &initCap);
				newAD = createAD(initCap);
				if(newAD == NULL)
				{
					printf("Unable to create AD\n");
					cont = 0;
				}
			break;
			case 2:
				printf("insert meeting room num: \n");
				scanf("%u", &room);
				printf("insert meeting start time: \n");
				scanf("%f", &begin);
				printf("insert meeting end time: \n");
				scanf("%f", &end);
				newMeet = CreateMeeting(room, begin, end);
				if(newMeet == NULL)
				{
					printf("didn't succeed to create your meeting\n");
				}
			break;
			case 3:
				flag = insAppToAD(newAD, newMeet);
				if(flag == 0)
				{
					printf("can't enter this meeting to calendar. Sorry )-:\n");
				} 
				else 
				{
					printf("meeting number = %d\n", flag);
				}
			break;
			case 4:
				printf("when the meeting you want to delete starts?\n");
				scanf("%f", &begin);
				flag = removeApp(newAD, begin);
				if(flag == -1)
				{
					printf("you don't have any meeting at %f.\n", begin);
				}
			break;
			case 5:
				printf("when the meeting you want to find starts?\n");
				scanf("%f", &begin);
				flag = find(newAD, begin);
				if(flag == -1){
					printf("you don't have any meeting at %f.\n", begin);
				} 
				else 
				{
					printf("meeting #%d for today. Good Luck!\n", flag+1);
				}
			break;
			case 6:
				printf("Are you sure you want to delete your array?\n0 - NO!!!\n1 - yes\n");
				scanf("%d", &flag);
				if(flag == 1)
				{
					destroy(newAD);
				}
			break;
			case 7:
				Print(newAD);
			break;
			case 8:
				printf("when the meeting you want to find starts?\n");
				scanf("%f", &begin);				
				if(findPtr(newAD, begin) != NULL)
				{
					printf("I found something\n");
				}
			break;
			case 9:
			    printf("Please insert file name:\n");
		        scanf("%s", fileName);
			    if((ExportToFile(newAD, fileName)) == 1)
			    {
			        printf("export succeed\n");
			    }
			break;			
			default: 
			    destroy(newAD);
			    cont = 0;
			break;
		}
	}
    return 1;

}
