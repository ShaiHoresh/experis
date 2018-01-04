#include <stdio.h>
#include "compNcat.h"

int main()
{
    char str1[40] = "abcd", str2[40] = "abCd", str3[40] = "abcd";
    int result;
	char str4[40] = "Shalom ", str5[40] = "al Israel";
	
    /* comparing strings str1 and str2	*/
    result = MYstrcmp(str1, str2);
    printf("MYstrcmp(str1, str2) = %d\n", result);

    /* comparing strings str1 and str3	*/
    result = MYstrcmp(str1, str3);
    printf("MYstrcmp(str1, str3) = %d\n", result);

    /*concatenates str1 and str2 and resultant string is stored in str1.*/
    MYstrcat(str4, str5);

    puts(str4);    
    puts(str5); 

     return 0;
}
