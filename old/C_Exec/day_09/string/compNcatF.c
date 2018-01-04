#include <stdio.h>
#include <string.h>
#include "compNcat.h"

int MYstrcmp(const char* str1, const char* str2){

	int diff = 0, i = 0;
	
	if(str1 == NULL || str2 == NULL){
		return -1;
	}
	
	while(diff == 0){
		if(str1[i] - str2[i] != 0){
			diff = str1[i] - str2[i];
		}
		if(str1[i] == '\0' && str2[i] == '\0'){
			diff = 0;
			break;
		}	
		++i;	
	}
	return diff;

}

char *MYstrcat(char *dest, const char *src){

	int length = strlen(dest), i = 0;
	
	
	if(dest == NULL){
		return NULL;
	}

	while(src[i] != '\0'){
		dest[length + i] = src[i];
		i++;
	}
	
	dest[length + i] = '\0';

}
