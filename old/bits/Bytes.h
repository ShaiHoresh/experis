#ifndef __BYTES_H__
#define __BYTES_H__

#define BYTESIZE 8
#define INTSIZE 32

unsigned char invert(unsigned char _x);

unsigned char rotate(unsigned char _x, int _numRot);

unsigned char SetBit(unsigned char _x, int _p, int _n, unsigned char _y);
unsigned int SetBits(unsigned int _w, int _i, int _j, int _value);

void PrintBinChar(unsigned char _x);
void PrintBinInt(unsigned int _x);

#endif /* #ifndef __BYTES_H__ */


