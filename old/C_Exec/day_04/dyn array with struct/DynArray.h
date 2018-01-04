#ifndef DYNARR_H
#define DYNARR_H

#define EXVAL 4

typedef struct{
	int*			array;
	unsigned int	NOE;
	unsigned int	capacity;
}dynarray;

dynarray* createDA(int capacity);
int insert(dynarray* DA, int N);
void destroy(dynarray* DA);

#endif
