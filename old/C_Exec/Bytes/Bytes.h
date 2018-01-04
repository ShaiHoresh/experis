#ifndef __BYTES_H__
#define __BYTES_H__

typedef struct{
    unsigned char* bits;
    int nof;
}bitMap;


typedef int(*BitFuncs)(bitMap* _bM, int _bitNum);

/*The function turn a bit on (if it was turned off)
gets the bitmap and the index the user wants to turn on
and returns 0 if the if failes (no bitmap or index out of range)
or 1 if succeeded*/
int BitOn(bitMap* _bM, int _bitNum);

/*The function turn a bit off (if it was turned on)
gets the bitmap and the index the user wants to turn on
and returns 0 if the if failes (no bitmap or index out of range)
or 1 if succeeded*/
int BitOff(bitMap* _bM, int _bitNum);

/*Checks if bit number '_bitNum' is on or off.
gets the bitmap and the index the user wants to turn on
and returns 0 if the bit is on, 1 if it is off or -1 if failed
(no bitmap or index out of range)*/
int IsBitOn(bitMap* _bM, int _bitNum);

bitMap* CreateBitMap(unsigned int _nof);
int DestroyBitMap(bitMap* _bM);

#endif /* #ifndef __BYTES_H__ */


