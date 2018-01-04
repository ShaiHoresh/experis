#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

int findNInsertWord(LibStruct* library, char* word);
int PrintLibrary(LibStruct* library);
LibStruct* createLib();
wordPtr CreateWord(LibStruct* library, char* word);
int extendArray(LibStruct* library);
LibStruct* destroy(LibStruct* library);

/*****************************************************************/
int printLastN(char* filename, unsigned int NumOfRows){

	FILE* fp;
	int i = 0, j;
	char row[300];
	int* array;
	
	array = malloc((NumOfRows + 1) * sizeof(int));
	if(NULL == array)
	{
	    return -1;
	}
	
	if((fp = fopen(filename,"r")) == NULL) return -1;
	
	while(1){
		fgets(row, 300 ,fp);
		if(feof(fp))
		{
		    break;
	    }
		array[i % (NumOfRows + 1)] = ftell(fp);
		i++;
		
	}

	fseek(fp, array[i % (NumOfRows + 1)], 0);
	while(1){
		fgets(row, 300, fp);
		if(feof(fp)) break;
		printf("%s\n", row);
	}				
	
	

	fclose(fp);
    return 0;
}


/*****************************************************************/
int RegOfChar(char* filename){

	int letterReg['Z' - 'A' + 'z' - 'a' + 2] = {0}, i;
	char ch;
	FILE* fp;
	
	if((fp = fopen(filename,"r")) == NULL) return -1;
	
	while(1){
		
		ch = fgetc(fp);
		if(isalpha(ch)){
			if(islower(ch)){
				letterReg[ch - 'a'] ++;
			} else {
				letterReg[ch - (2 * 'A') + 'Z'] ++;
			}
		}
		if(feof(fp)) break;
	}
	
	for(i = 0; i < ('z' - 'a' + 1); ++i){
		if(letterReg[i] > 0){
			printf("%c	%d\n", i + 'a', letterReg[i]);
		}
	}
	for(i = ('z' - 'a' + 1); i < 2 * ('z' - 'a' + 1); ++i){
		if(letterReg[i] > 0){
			printf("%c	%d\n", i - ('z' - 'a' + 1) + 'A', letterReg[i]);
		}
	}
	
	fclose(fp);
	
	return 1;		
}

int RegOfwords(char* filename){
	

	LibStruct* Lib;
	char row[300];
	char* word;
    FILE* fp;

	Lib = createLib();
	if((fp = fopen(filename,"r")) == NULL)
	{
	    return -1;
    }
	
	while(1)
	{
		if(feof(fp))
		{
		    break;
	    }
		fgets(row, 300 ,fp);

        word = strtok(row, "()' %,.-`;!?\"\n");
        while (word != NULL)
        {
		    if(feof(fp))
		    {
		        break;
	        }
            findNInsertWord(Lib, word);
            printf("*%s* ", word);
            word = strtok(NULL, "()'% ,.-`;!?'\"\n");
        }
    }
    printf("\n");
    PrintLibrary(Lib);
    fclose(fp);
    destroy(Lib);
    return 0;

}

LibStruct* createLib()
{	
	wordPtr* tmp;
	unsigned int capacity;
	LibStruct* library;
	
	capacity = 50;
	library = malloc(sizeof(LibStruct));
	
	if(library != NULL)
	{
		tmp = malloc(capacity * sizeof(wordPtr));
	}
	
	if(tmp != NULL)
	{
		library -> busy = 0;
		library -> array = tmp;
		library -> capacity = capacity;
	} 
	else
	{
		free(library);
		return NULL;
	}
	return library;
}

/*****************************************************************/
wordPtr CreateWord(LibStruct* library, char* word){
	
	wordPtr	newWord;

	if(library -> capacity == library -> busy)
	{
		if(extendArray(library) == 0)
		{
			return NULL;
		}
	}
	newWord = malloc(sizeof(words));
	if(newWord == NULL)
	{
	    return NULL;
    }
	
	newWord -> word = word;
	newWord -> counter = 1;
	
	return newWord;
}

/*****************************************************************/

int findNInsertWord(LibStruct* library, char* _word){

	int i = 0;
	wordPtr	newWord;
/*	printf("%s       =? ", _word);*/
	for(i = 0; i < library -> busy; ++i){
		if(strcmp(library -> array[i] -> word, _word)==0){
		    ++(library -> array[i] -> counter);
/*		    printf("%s %d times\n", library -> array[i] -> word, library -> array[i] -> counter);*/
			return i;
		}
	}

	newWord = CreateWord(library, _word);
	library->array[i] = newWord;
	++library->busy;
/*	printf("%s  first\n", library -> array[i] -> word);*/
	return i;
}

/*****************************************************************/
int extendArray(LibStruct* library){
	wordPtr* temp;
	
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

LibStruct* destroy(LibStruct* library)
{

	int i;
	
	if(library){
		if(library -> array){
			for(i = 0; i < library -> busy; ++i){
				free(library -> array[i]);
			}
			free(library -> array);
		}
		free(library);
	}
    return NULL;
}

/*****************************************************************/

int PrintLibrary(LibStruct* library)
{
	int i;
	
	for(i = 0; i < library->busy; ++i)
	{
		printf("%s	%d\n", library->array[i]->word, library->array[i]->counter);
	}
	return 0;
}


		














		
