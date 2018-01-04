#ifndef FILES_STRINGS_H
#define FILES_STRINGS_H

typedef struct{
	char*           word;
	unsigned int    counter;
}words;

typedef words* wordPtr;

typedef struct{
	wordPtr*		array;
	unsigned int	busy;
	unsigned int	capacity;
}LibStruct;

int printLastN(char* filename, unsigned int NumOfRows);
int RegOfChar(char* filename);
int RegOfwords(char* filename);

#endif
