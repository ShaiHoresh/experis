#include <stdio.h>
#include "string.h"

int main(){

	char str[32] = "abcdefg";
	char str2[32] = "abcdcba";
	char str3[32] = "abcdef";
	char numstr[32] = "12345";
	char numstr2[32] = "12a45";
	int flag = 0;
	int num = 321456;
	char* strPtr;
	
	printf("%s\n", str);
	flag = reverseString(str);
	printf("flag of rev %d\n", flag);
	printf("%s\n", str);
	
	printf("%s\n", str3);
	flag = reverseString(str3);
	printf("flag of rev %d\n", flag);
	printf("%s\n", str3);
	
	flag = PalinString(str);
	printf("%d\n", flag);
	
	flag = PalinString(str2);
	printf("%d\n", flag);
	
	printf("%d\n", myAtoI(numstr));	
	printf("%d\n", myAtoI(numstr2));
	
	strPtr = myItoA(num);
	printf("%s\n", strPtr);	
		
}
