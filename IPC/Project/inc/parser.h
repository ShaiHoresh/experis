#ifndef __PARSER_H__
#define __PARSER_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "comm.h"


typedef void(*CBack)(CDRData*);

void ParseCdr(char* _fileName, CBack _cb);

#endif /* __PARSER_H__ */

