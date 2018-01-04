#include <stdio.h>

void func1(int n);
void func2(int n);
void func3(int n);

void main(){
	int num=0;
	printf("Please write a number\n");
	scanf("%d", &num);
	func1(num);
	func2(num);
	func3(num);
	return;
}

void func1(int n){

	int i, j;
	for(i=0; i<n+1; ++i){
		for(j=0; j<i; ++j){
			printf("*");
		}
		printf("\n");
	}

}

void func2(int n){
	int i, j;
	func1(n);
	for(i=n-1; i>0 ; --i){
		for(j=0; j<i; ++j){
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
}

void func3(int n){

	int i, j, mid;
	mid = n - 1;
	for(i=0; i<n; ++i){
		for(j=0; j<mid; ++j){
		printf(" ");
		}
		for(j=0; j<2*i+1; ++j){
			printf("*");
		}
		printf("\n");
		--mid;
	}
	printf("\n");
}

