#ifndef AD_H
#define AD_H


#define EXVAL 4
#define CAPACITY 8

typedef struct
{
	unsigned int	room;
	float	begintime;
	float	endtime;
}meeting;

typedef meeting* meetPtr;

typedef struct
{
	meetPtr*		array;
	unsigned int	numOfMeetings;
	unsigned int	capacity;
}ADstruct;

/*This function creates the daily meetings. the function returns a pointer to the calendar, or null if didn't succeed*/
ADstruct* createAD(unsigned int capacity);

/*This function creates a meeting, by inserting the room #, time of beggining and and and creating the struct*/
meetPtr CreateMeeting(unsigned int room, float begintime, float endtime);

/*Checking if the time of the meeting isn't overlapping and inserts the meeting to the calendar*/
int insAppToAD(ADstruct* AD, meetPtr newmeet);

/*removing a meeting by beginning time */
int removeApp(ADstruct* AD, float begintime);

/*free all the memory allocation that the program created*/
ADstruct* destroy(ADstruct* AD);

/*prints all the meeting there are in the calendar, sorted by beginning time*/
void Print(ADstruct* AD);

/* Import meetings to an AD from .txt file */
ADstruct* ImportCalFromFile(char* _fileName);

/*Exports the data from AD to a.txt file */
int ExportToFile(ADstruct* _AD, char* _fileName);



int find(ADstruct* AD, float begintime);
meetPtr findPtr(ADstruct* AD, float begintime);

#endif

