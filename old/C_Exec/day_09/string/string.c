#include <stdio.h>
#include "string.h"

int main(){

	char str[32] = "abcdefg";
	char str2[32] = "abcdcba";
	char str3[32] = "abcdef";
	char numstr[32] = "12345";
	char numstr2[32] = "12a45";
	int flag = 0;
	int num = -521456;
	char* strPtr;
	char strnum[32];
	
	printf("first srtring: %s\n", str);
	flag = reverseString(str);
	printf("flag of rev %d\n", flag);
	printf("reversed string: %s\n\n", str);
		
	printf("second: %s\n", str3);
	flag = reverseString(str3);
	printf("flag of rev %d\n", flag);
	printf("reversed string: %s\n\n", str3);
	
	flag = PalinString(str);
	printf("the string is %s.flag = %d. 1 for palin, -1 - not a palin.\n\n", str, flag);
	
	flag = PalinString(str2);
	printf("the string is %s.flag = %d. 1 for palin, -1 - not a palin.\n\n", str2, flag);
	
	printf("num was string. now it's an int: %d\n", myAtoI(numstr));	
	printf("the string: %s has the letter 'a', so we get '%d' instead of garbage.\n\n", numstr2, myAtoI(numstr2));	

	strPtr = myItoA(num, strnum);
	printf("num was an int. now it's a string: %s\n\n", strnum);
		
}
