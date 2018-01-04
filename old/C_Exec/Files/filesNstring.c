#include <stdio.h>
#include "filesNstring.h"

#define N 5

int main(){


	int flag = 0;
	flag = RegOfChar("alice");
	
	printLastN("alice", N);
	RegOfwords("alice");
	if(flag == 0) printf("something wrong\n");
	
	
	return 0;
}
