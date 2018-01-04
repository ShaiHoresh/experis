#ifndef _ENUM_H_
#define _ENUM_H_

enum ADTErr {

    ERR_OK                  = 0,
    ERR_GENERAL             = 1,
    ERR_NOT_INITIALIZED     = 2,
    ERR_ALLOCATION_FAILED   = 3,
    ERR_REALLOCATION_FAILED = 4,
    ERR_UNDERFLOW           = 5,
    ERR_OVERFLOW            = 6,
    ERR_WRONG_INDEX         = 7,
    ERR_STACK_BBBBB        = 30
};

typedef enum ADTErr ADTErr;

#endif /*#ifndef _ENUM_H_*/
