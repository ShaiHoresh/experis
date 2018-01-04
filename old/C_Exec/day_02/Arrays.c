#include <stdio.h>

void SortZeroOne(int array[], int num);
int Sort(int array[], int num);
void swap(int* x, int* y);
int repeat(int array[],int num);

void main(){
	int size=6;
	int array[size], i;
	
	printf("This part is sortings 0-s and 1-s/\nPlease, enter %d digits - 0 or 1:\n", size);
	for(i=0; i<size; ++i){
		scanf("%d", &array[i]);
	}

	SortZeroOne(array, size);
	for(i=0; i<size; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");				
/**************************************************************************/	
	printf("\nThis part is seperating between the even to the odd numbers and return the num of even numbers.\nPlease, enter %d numbers:\n", size);
	for(i=0; i<size; ++i){
		scanf("%d", &array[i]);
	}
	printf("The number of even numbers in this array is: %d\n", Sort(array, size));
	for(i=0; i<size; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");	
							
/***************************************************************************/	
	printf("\nThis part is checking what is the most common num in the array you are going to type.\nPlease, enter %d numbers:\n", size);
	for(i=0; i<size; ++i){
		scanf("%d", &array[i]);
	}
	printf("the most common num is %d\n", repeat(array, size));
}

void SortZeroOne(int array[], int num){
	int i, counter=0;
	for(i=0; i<num; ++i){
		array[i]==0 ? ++counter : counter;
	}
	printf("%d\n", counter);
	for(i=0; i<counter; ++i){
		array[i]=0;
	}
	for(i=counter; i<num; ++i){
		array[i]=1;
	}
}

int Sort(int array[], int num){
	int i, j, flag = 1, even = 0;
	for(i=0; i<num; ++i){
		array[i]%2==0 ? ++even : even;
	}
	for(i=1; i<num && flag==1; ++i){
		flag = 0;
		for(j=0; j<num-i; ++j){
			if(array[j]%2!=0&&array[j+1]%2==0){
			swap(&array[j], &array[j+1]);
			flag = 1;
			}	
		}
	}
	return even;
}

/**********************************************************************/

void swap(int* x, int* y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int repeat(int array[],int num){
	int i, j, flag=0, tempcounter, max=0;
	
	for(i=0; i<num; ++i){
		tempcounter=0;
		for(j=i; j<num; ++j){
			if(array[j]==array[i]){
				++tempcounter;
			} 
		}
		if(tempcounter>max){
			max=tempcounter;
			flag = array[i];
		}
	}
	return flag;
}
