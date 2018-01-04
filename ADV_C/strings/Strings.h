#ifndef __STRINGS_H__
#define __STRINGS_H__


/*DESC: finding the length of the string.
INPUT:  a string.
OUTPUT: length (size_t).
ERROR:  0 if string doesn't exist.
*/
size_t StrLen(const char* _str);
size_t StrLenRec(const char* _str);

/*DESC: Checking if the strings are identical.
INPUT:  two strings.
OUTPUT: 0 for identical string, else for different.
ERROR:  none.
*/
int StrCompare(const char* _s1, const char* _s2);
int StrCompareRec(const char* _s1, const char* _s2);

/*DESC: Copy source string to destination.
INPUT:  two strings.
OUTPUT: destination string identical to the source.
ERROR:  NULL if one (or more) of the strings is NULL.
*/
char* StrCopy(char* _destination, const char* _source);
char* StrCopyRec(char* _destination, const char* _source);

/*DESC: Copy N charcters from source string to destination.
INPUT:  two strings.
OUTPUT: N charcters of destination string identical to the source.
ERROR:  NULL if one (or more) of the strings is NULL.
*/
char* StrNCopy(char* _destination, const char* _source, size_t _num);
char* StrNCopyRec(char* _destination, const char* _source, size_t _num);

/*DESC: Copy source string right after destination.
INPUT:  two strings.
OUTPUT: unified string.
ERROR:  NULL if one (or more) of the strings is NULL.
*/
char* StrConcat(char* _destination, const char* _source);


char* StrSubString(char* _str, const char* _search);

#endif /* __STRINGS_H__ */
