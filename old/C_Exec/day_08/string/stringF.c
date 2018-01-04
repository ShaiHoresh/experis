#include <string.h>
#include <stdio.h>

void swap(char* x, char* y);

int reverseString(char* str){

	int length = strlen(str);
	int i;
	
/*	if(length % 2 == 1){
		length --;
	}*/
	
	if(str == NULL) return 0;

	for(i = 0; i < length / 2; ++i){
		swap(&str[i], &str[length - i]);		
	}
	
	return 1;
	
}

int PalinString(char* str){

	int length = strlen(str) - 1;
	int i, flag = 1;
	
	if(str == NULL) return 0;

	for(i = 0; i < length / 2; ++i){
		if(str[i] != str[length - i]){
			flag = -1;
		}
				
	}
	
	return flag;	
}

int myAtoI(char* str){
	
	int i, number = 0;
	int length = strlen(str);

	if(str == NULL) return 0;

	for(i = 0; i < length ; ++i){
		if(str[i] < 48 || str[i] > 57){
			return 0;
		}
		number = number * 10 + str[i] - '0';
	}				
	
	return number;
}

char* myItoA(int number){

	int i=0, flag = 0;
	char strnum[32];
	char* str;
	printf("%d\n", number);
	while(number / 10 != number){
		strnum[i] = (number % 10) + '0';
		printf("%c\n", strnum[i]);
		number /= 10;
		++i;
	}
	strnum[i] = '\0';
	flag = reverseString(strnum);
	str = strnum;
	if(flag == 1) return str;
}



void swap(char* x, char* y){
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
