#include <stdio.h>

int binSearch(int array[], int val, int size);

void main(){
	int size = 8, i;
	int sarr[8]={-5,2,3,4,8,12,14,23};
	int des_val;
	
/*	printf("Please enter the number you are looking for\n");
	scanf("%d", &des_val);
	printf("your number location is: %d\n", binSearch(sarr, des_val, size));		*/
	
	for(i = 0; i<size; ++i){
		printf("the location of %d is %d\n", sarr[i], binSearch(sarr, sarr[i], size));
	}
	
}

int binSearch(int array[], int val, int size){
	int	tmp = 0, mid = size;
	
	if(array[0]==val)		return 0;
	while(mid/2>0){
		if(val==array[tmp])	return tmp;
		else if(val>array[tmp]){
			tmp = tmp + mid / 2;
			mid=mid/2;
			printf("val = %d, mid = %d, tmp = %d, array[tmp] = %d\n", val, mid, tmp, array[tmp]);
		} else if(val<array[tmp]) {
			tmp = tmp - mid / 2;
			mid=mid/2;
			printf("val = %d, mid = %d, tmp = %d, array[tmp] = %d\n", val, mid, tmp, array[tmp]);
		}
	}
	return tmp;
}
