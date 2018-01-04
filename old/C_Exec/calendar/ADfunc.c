#include <stdio.h>
#include <stdlib.h>
#include "AD.h"

int shiftLeft(ADstruct* AD, unsigned int index);
int shiftRight(ADstruct* AD, unsigned int index);
ADstruct* ImportCalFromFile(char* _fileName);
int ExportToFile(ADstruct* _AD, char* _fileName);


/*********************************************************************************/
ADstruct* createAD(unsigned int capacity){
	
	meetPtr* temp;
	ADstruct* AD = malloc(sizeof(ADstruct));
	
	if(AD != NULL)
	{
	    temp = malloc(capacity*sizeof(meetPtr));
 	}
 	if(temp != NULL)
 	{
		AD -> numOfMeetings = 0;
		AD -> array = temp;
		AD -> capacity = capacity;	
		return AD;
	} 
	else 
	{
		free(AD);
	}
	return NULL;
}

/**********************************************************************************/
meetPtr CreateMeeting(unsigned int room, float begintime, float endtime){
	
	meetPtr newMeet = malloc(sizeof(meeting));
	
	if(newMeet == NULL){
		return NULL;
	}
	if(begintime < 0 || endtime > 24){
		return NULL;
	}
	if(begintime >= endtime){
		return NULL;
	}
	
	newMeet -> room = room;
	newMeet -> begintime = begintime;
	newMeet -> endtime = endtime;
	
	return newMeet;
	
}

/**********************************************************************************/
int insAppToAD(ADstruct* AD, meetPtr newmeet){

	int index = -1; 
	int temp;
	
	if(AD == NULL){
		return 0;
	}
	
	if(AD -> numOfMeetings == 0)
	{
		index = 0;
	}
	else if(AD->array[AD->numOfMeetings - 1]->endtime <= newmeet->begintime)
	{
		index = AD -> numOfMeetings;
	}
	else if(AD->array[0]->begintime >= newmeet->endtime)
	{
		index = 0;	
	}
	else
	{
		index = 1;
		while(index < (AD->numOfMeetings))
		{
			if(newmeet -> begintime >= AD -> array[index - 1] -> endtime && newmeet -> endtime <= AD -> array[index] -> begintime)
			{
				break;
			}
			++index;
		}
	}
	
	temp = shiftRight(AD, index);

	if(temp == 0) 
	{
	    free(newmeet);
	    return 0;
	}
	
	AD -> array[index] = newmeet;
	AD -> numOfMeetings ++;

	return 1;

}

/**********************************************************************************/
int removeApp(ADstruct* AD, float begintime){

	int index;
	
	index = find(AD, begintime);
	
	if(index == -1) return -1;
	
	shiftLeft(AD, index);
	AD -> numOfMeetings--;
	return 1;

}

/**********************************************************************************/
int find(ADstruct* AD, float begintime){
	
	int i;
	
	for(i=0; i < AD -> numOfMeetings; ++i){
		if(AD -> array[i] -> begintime == begintime){
			return i;
		}	
	}
	return -1;
}

/**********************************************************************************/
meetPtr findPtr(ADstruct* AD, float begintime){
	
	int i;
	if(AD)
	for(i=0; i < AD -> numOfMeetings; ++i){
		if(AD -> array[i] -> begintime == begintime){
			return AD -> array[i];
		}	
	}
	return NULL;
}

/**********************************************************************************/
int shiftLeft(ADstruct* AD, unsigned int index){

	int i;

	if(index == -1) return -1;
	free(AD -> array[index]);		/*I need to complete this row*/
	for(i = index; i < AD -> numOfMeetings; ++i){
		AD -> array[i] =AD -> array[i+1];
	}
	return 1;
}

/**********************************************************************************/
int shiftRight(ADstruct* AD, unsigned int index){

	int i;
	meetPtr* temp = AD -> array;
	
	if(index > AD -> numOfMeetings) return 0;
	
	if(AD -> numOfMeetings >= AD -> capacity)
	{
		temp = realloc(AD -> array, (AD -> capacity +EXVAL) * sizeof(meetPtr));
	}
	
	if(temp == NULL)
	{
	    return 0;
    }

	AD -> capacity += EXVAL;
	AD -> array = temp;
	
	for(i = AD -> numOfMeetings; i > index; --i)
	{
		AD -> array[i] = AD -> array[i - 1];
	}
	
	return 1;
	
}

/**********************************************************************************/

ADstruct* destroy(ADstruct* AD){

	int i;
	
	if(AD){
		if(AD -> array){
			for(i = 0; i < AD -> numOfMeetings; ++i){
				free(AD -> array[i]);
			}
			free(AD -> array);
		}
		free(AD);
	}
	return NULL;
}

/**********************************************************************************/
void Print(ADstruct* AD){

	int i;

	if(AD != NULL && AD -> numOfMeetings > 0){
		printf("Your meetings today: \n");
		for(i = 0; i < AD -> numOfMeetings; ++i){
			printf("meeting #%d: start at %4.2f, end at %4.2f, in room #%d\n\n", i, AD -> array[i] -> begintime, AD -> array[i] -> endtime, AD -> array[i] -> room);
		}
	}else {
		printf("you are free!!! (-;\n\n");
	}
	
}

int ExportToFile(ADstruct* _AD, char* _fileName)
{
    FILE* fP;
    int i;

    if(NULL == _fileName || NULL == _AD)
    {
        return 0;
    }
    if((fP = fopen(_fileName, "w")) == NULL)
    {
        return 0;
    }    
    
    for(i = 0; i < _AD->numOfMeetings; ++i)
    {
        fprintf(fP, "%d %4.2f %4.2f\n", _AD->array[i]->room, _AD->array[i]->begintime, _AD->array[i]->endtime);
    }
    fclose(fP);
    return 1;
}


ADstruct* ImportCalFromFile(char* _fileName)
{
    ADstruct* AD;
    FILE* fP;
    unsigned int room;
    float begin, end;
    char row[64];
    meetPtr meeting;
    int flag;
    
    AD = createAD(CAPACITY);
    
    if(NULL == _fileName || (fP = fopen(_fileName, "r+")) == NULL)
    {
        return NULL;
    }
    
    while(1)
    {
        fgets(row, 64, fP);
        if(feof(fP))
	    {
	        break;
        }

        sscanf(row, "%u %f %f", &room, &begin, &end);
        meeting = CreateMeeting(room, begin, end);

        if(NULL == meeting)
        {
            fclose(fP);
            return 0;
        }
        flag = insAppToAD(AD, meeting);

        if(flag == 0)
        {
            fclose(fP);
            return 0;
        }
    }
    fclose(fP);
    return AD;
}


























