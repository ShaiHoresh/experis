#ifndef AD_H
#define AD_H

#define EXVAL 4

typedef struct{
	unsigned int	room;
	float	begintime;
	float	endtime;
}meeting;

typedef meeting* meetPtr;

typedef struct{
	meetPtr*		array;
	unsigned int	numOfMeetings;
	unsigned int	capacity;
}ADstruct;


ADstruct* createAD(unsigned int capacity);
meetPtr CreateMeeting(unsigned int room, float begintime, float endtime);
int insAppToAD(ADstruct* AD, meetPtr newmeet);
int removeApp(ADstruct* AD, float begintime);
int find(ADstruct* AD, float begintime);
int shiftLeft(ADstruct* AD, float begintime);
int shiftRight(ADstruct* AD, float begintime);
ADstruct* destroy(ADstruct* AD);
void Print(ADstruct* AD);
meetPtr findPtr(ADstruct* AD, float begintime);

#endif

/*

dynarray* createDA(int capacity);
int insert(dynarray* DA, intptr N);
void destroy(dynarray* DA);
int InsertToIndex(dynarray* DA, int* numPtr, unsigned int index);
int* Find(dynarray* DA, int num);	
int Remove(dynarray* DA, int num);
int Print(dynarray* DA);
int shiftLeft(dynarray* DA, unsigned int index);
int shiftRight(dynarray* DA, unsigned int index);

	
Create AD 																		v
Create meeting (check that times are logical!)									v
Insert appointment into AD – insertion in sorted order ( by begin hour )
Remove appointment from AD ( by begin hour)										v
Find appointment in AD (by begin hour)											v
Destroy AD
Print AD

*/
