#include <stdio.h>
#include <math.h>

int Prime(int n);
int Palin(int n);
int Ascending(int n);
int Reverse(int n);

void main(){
	int num=0;
//	printf("Is the number is prime?\n);
	printf("Please write a number\n");
	scanf("%d", &num);
	if(Prime(num)==0){
		printf("\nThis number is odd\n\n");
	} else
		printf("\nThe number is prime\n\n"); 

//	printf("Is the number is palindram?\nPlease write a number\n");
//	scanf("%d", &num);	
	if(Palin(num)==1){
		printf("the num is palin\n\n");
		} else
		printf("the num is not a palin\n\n");
		
//		printf("Is the number is ascending?\nPlease write a number\n");
//	scanf("%d", &num);	
	if(Ascending(num)==1){
		printf("the num is ascending\n\n");
		} else
		printf("the num is not ascending\n\n");
				
//		printf("Let's go reverse!\nPlease write a number\n");
//	scanf("%d", &num);	 
	printf("In reverse mode: %d\n\n", Reverse(num));	
}
	
int Prime(int n){
	int i;
	float sq;
	
	if(n<=0){
		return 0;
	}
	if(n>0 && n<4){
		return 1;
	}
	if(n%2==0){
		return 0;
	}
	sq=sqrt(n);
	for(i=5; i<sq; i+=2){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}

int Palin(int n){

	int counter=0, temp = n ,i, pow, big, small;
	
	if(n%10==n)	return 1;
	
	while(temp>=1){							/* finding the num of digits in the number*/
		++counter;
		temp /= 10;
	}
	counter--;
	while(counter > 0){						/* this loop is checking if the edges are equal*/
		pow = 1;							/* and then cuts them*/
		for(i=0; i<counter; ++i){
			pow = pow * 10;
		}									
		big = n / pow;
		small = n % 10;
		if(big != small){
			return 0;
		}
		counter -= 2;
		n = (n % pow) / 10;	
	}
	return 1;
}


int Ascending(int n){

	int a, b;
	while(n/10 > 0){
		a = n % 10;
		b = (n / 10) % 10;
		if(b >= a)	return 0;
		n = n / 10;
	}
	return 1;	
}

int Reverse(int n){
	int temp = 0, a;
	while(n/10 > 0){
		a = n % 10;
		temp = temp * 10 + a;
		n = n / 10;
	}
		a = n % 10;
		temp = temp * 10 + a;
		n = n / 10;
	return temp;
}

