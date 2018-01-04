#include <stdio.h>
#include <string.h>
#include <ctype.h>


int findNInsertWord(LibStruct* library, char* word);
int PrintLibrary(LibStruct* library);
LibStruct* createLib();
wordPtr CreateWord(LibStruct* library, char* word);
int extendArray(LibStruct* library);
Libstruct* destroy(Libstruct* library);

/*****************************************************************/
int printLastN(char* filename, unsigned int NumOfRows){

	FILE* fp;
	int array[NumOfRows+1], i = 0;
	char row[300];
	
	if((fp = fopen(filename,"r")) == NULL) return -1;
	
	while(1){
		
		fgets(row, 300 ,fp);
		if(feof(fp)) break;
		array[i % (NumOfRows+1)] = ftell(fp);
		i++;
		
	}

	fseek(fp, array[i % (NumOfRows+1)], 0);
	while(1){
		fgets(row, 300, fp);
		if(feof(fp)) break;
		printf("%s\n", row);
	}				
	
	

	fclose(fp);

}


/*****************************************************************/
int RegOfChar(char* filename){

	int letterReg[52] = {0}, i;
	char ch;
	FILE* fp;
	
	if((fp = fopen(filename,"r")) == NULL) return -1;
	
	while(1){
		ch = fgetc(fp);
		if(isalpha(ch)){
			if(islower(ch)){
				letterReg[ch - 'a'] ++;
			} else {
				letterReg[ch - 'A' + 26] ++;
			}
		}
		if(feof(fp)) break;
	}
	
	for(i = 0; i < 26; ++i){
		if(letterReg[i] > 0){
			printf("%c	%d\n", i + 'a', letterReg[i]);
		}
	}
	for(i = 26; i < 52; ++i){
		if(letterReg[i] > 0){
			printf("%c	%d\n", i - 26 + 'A', letterReg[i]);
		}
	}
	
	fclose(fp);
	
	return 1;		
}


/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
int RegOfwords(char* filename)
{
	char* word;
	libstruct* LIB;
	LIB = createLib();
	char row[1000];
	while(NULL != word)
    {
        fgets(row, 1000, fp);
        word = strtok (NULL, " ?!,.-");
        findNInsertWord(library, word);
    }
    PrintLibrary(library);
    
    destroy(library);
}
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/


LibStruct* createLib(){
	
	array* = tmp;
	capacity = 20;
	LibStruct* Lib = malloc(sizeof(LibStruct));
	
	if(Lib != NULL){
		tmp = malloc(capacity * sizeof(array));
	}
	
	if(tmp != NULL){
		Lib -> busy = 0;
		Lib -> array = tmp;
		Lib -> capacity = 20;
	return Lib;
	} else {
		free(Lib);
		return NULL;
	}
}

/*****************************************************************/
wordPtr CreateWord(LibStruct* library, char* word){
	
	if(library -> capacity == library -> busy){
		if(extendArray(library) == 0){
			return NULL;
		}
	}
	wordPtr	newWord = malloc(sizeof(words));
	if(newWord == NULL) return NULL;
	
	newWord -> word = word;
	newWord -> counter = 1;
	
	
	return newWord;
}

/*****************************************************************/

int findNInsertWord(LibStruct* library, char* word){

	int i;
	if(library->busy == library->capacity)
	{
	    extendArray(library);
	}
	for(i = 0; i < library -> busy; ++i){
		if(strcmp(library -> array[i] -> word, word)==0){
			library -> array[i] -> counter ++;
			return i;
		}
	}
	
	createWord(library, word);
	return ++i;
}

/*****************************************************************/
int extendArray(LibStruct* library){
	LibStruct* temp;
	
	if(library -> capacity == library -> busy){
		temp = realloc(library -> array, (library -> capacity * 2) * sizeof(wordPtr));
	}
	
	if(temp != NULL){
		library -> capacity *= 2;
		library -> array = temp;
		return 1;
	}
	return 0;	
}

/*****************************************************************/

Libstruct* destroy(Libstruct* library){

	int i;
	
	if(library){
		if(library -> array){
			for(i = 0; i < library -> busy; ++i){
				free(library -> array[i];
			}
			free(library -> array);
		}
		free(library);
	}

}

/*****************************************************************/

int PrintLibrary(LibStruct* library){

	int i;
	
	for(i = 0; i < library -> busy; ++i){
		printf("%s	%d\n", library -> array[i] -> word, library -> array[i] -> counter);
	}
}

/*
typedef struct{
	char* 			word;
	unsigned int	counter;
}words;

typedef 	words*	wordPtr;

typedef struct{
	wordPtr*		array;
	unsigned int	busy;
	unsigned int	capacity;
}LibStruct;			














		*/
