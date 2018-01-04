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
int shiftLeft(ADstruct* AD, unsigned int index);
int shiftRight(ADstruct* AD, unsigned int index);
ADstruct* destroy(ADstruct* AD);
void Print(ADstruct* AD);
meetPtr findPtr(ADstruct* AD, float begintime);

#endif

