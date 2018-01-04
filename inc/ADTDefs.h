#ifndef __ADTDefs_H__
#define __ADTDefs_H__

typedef enum Vector_Result {
	VECTOR_SUCCESS,
	VECTOR_UNITIALIZED_ERROR,				/**< Uninitialized vector error 	*/
	VECTOR_ALLOCATION_ERROR,				/**< realloc error on grow/shrink   */
	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR
	/* Add more as needed by your implementation */
} Vector_Result;


typedef enum
{
    /* General ADT Errors */
    ERR_OK                            =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    /* Vector Errors */
    /* Stack  Errors */
    ERR_STACK_BBBBB = 30,
    /* LinkedList  Errors */
    /* Bit Vector*/
    ERR_INSERT_FAILED,
    ERR_INVALID_VALUE,
    ERR_INVALID_SIZE
} ADTErr;

#endif /*#ifndef __ADTDefs_H__*/
