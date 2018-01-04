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

#endif
