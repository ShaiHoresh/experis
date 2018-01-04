#include <stdio.h>

float Average(int array[], int num);

void main(){
	int array[4], i;
	
	for(i=0; i<4; ++i){
		printf("\nenter a number: ");
		scanf("%d", &array[i]);
	}
	printf("\nThe average of the number is: %f\n", Average(array, 4));
}


float Average(int *array, int num){
	int i;
	float sum = 0.0, Ave;
	for(i=0; i<num; ++i){
		sum += array[i];
		}
	Ave = sum / num;
	return Ave;
}
