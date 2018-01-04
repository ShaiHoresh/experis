#ifndef LOTTO
#define LOTTO

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 49
#define NUM 6

/*	the function gets an array with NUM cells and randomize numbers
	in the RANGE */
int* randNum(int randNumArray[], unsigned int num);

/*	the function gets array (with rand numbers?) and prints the number
	in a card format*/
int Printcard(int randNumArray[], unsigned int num);

#endif


