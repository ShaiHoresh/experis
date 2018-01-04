#ifndef DYNARR_H
#define DYNARR_H

#define EXVAL 4

typedef int* intptr;
typedef intptr* ipp;

typedef struct{
	intptr*			array;
	unsigned int	NOE;
	unsigned int	capacity;
}dynarray;

dynarray* createDA(int capacity);
int insert(dynarray* DA, intptr N);
void destroy(dynarray* DA);
int InsertToIndex(dynarray* DA, int* numPtr, unsigned int index);
int* Find(dynarray* DA, int num);	
int Remove(dynarray* DA, int num);
int Print(dynarray* DA);
int shiftLeft(dynarray* DA, unsigned int index);
int shiftRight(dynarray* DA, unsigned int index);

#endif
