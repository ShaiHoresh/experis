#include "lotto.h"


int main(){
	
	int array[NUM]={0};

	int* a;
	a = randNum(array, NUM);
	
	Printcard(a, NUM);
	
	return 0;
}

