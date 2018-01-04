#include <string.h>

int reverseString(char* str){

	int length = strlen(str);
	int i;
	
	if(str = NULL) return 0;
	
	for(i = 0; i < length / 2; ++i){
		str[i] = str[length - i];
	}
	
	return 1;
	
}

int PalinString(char* str){



}
