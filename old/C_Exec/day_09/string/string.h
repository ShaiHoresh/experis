#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <string.h>

int myAtoI(char* str);			/*convert a number from string type to integer. if there is any character that is not a digit the func return 0*/
char* myItoA(int number, char* strnum);
int reverseString(char* str);	/*return 1 if succeeded and 0 if failed - meaning *str = NULL*/
int PalinString(char* str);		/*return 1 if succeeded, 0 if failed - meaning *str = NULL and -1 if it is not a palindrome*/


#endif
