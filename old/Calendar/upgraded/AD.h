#ifndef AD_H
#define AD_H


#define EXVAL 4
#define CAPACITY 8

typedef enum
{
    /* General ADT Errors */
    ERR_OK                            =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_FILE,
    /* Vector Errors */
    /* Stack  Errors */
    ERR_STACK_BBBBB = 30
    /* LinkedList  Errors */
    /* Bit Vector*/
} ADTErr;

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
ADTErr insAppToAD(ADstruct* AD, meetPtr newmeet);

/*removing a meeting by beginning time */
ADTErr removeApp(ADstruct* AD, float begintime);

/*free all the memory allocation that the program created*/
ADTErr destroy(ADstruct* AD);

/*prints all the meeting there are in the calendar, sorted by beginning time*/
ADTErr Print(ADstruct* AD);

/* Import meetings to an AD from .txt file */
ADTErr ImportCalFromFile(ADstruct* AD, char* _fileName);

/*Exports the data from AD to a.txt file */
ADTErr ExportToFile(ADstruct* _AD, char* _fileName);

int find(ADstruct* AD, float begintime);
meetPtr findPtr(ADstruct* AD, float begintime);

#endif

