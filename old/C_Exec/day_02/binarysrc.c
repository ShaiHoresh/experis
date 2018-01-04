#include <stdio.h>

int binsrc(array[], req, len);

void main(){
	int size = 8;
	int arr[size]={1,2,3,4,5,6,7,8}, i, wanted;
	
	printf("enter the num you want to find\n");
	scanf("%d", &wanted);
	printf("the number location is: %d\n", binsrc(arr,wanted, size));

}

int binsrc(array[], req, len){
	int i, ll, hl;							/* ll for low-limit, hl for high-limit */
	
	
}
