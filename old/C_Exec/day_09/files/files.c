#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGH 40

int main(){

	char name[MAX_NAME_LENGH];
	unsigned int age;
//	int i, end, begin;
	FILE* fp = NULL;
	
	fp = fopen("Yosi", "w");
	if (NULL == fp) {
		return -1;
	}
	while(1) {
		printf("Please enter name anf age of a person: ");
		scanf("%s%d", name, &age);
		if (age < 1) break;
		fprintf(fp, "%s %d\n", name, age);
	}
	fclose(fp);
	
	if((fp = fopen("FILES", "w")) == NULL){
		printf("Can't open the file\n");
	}
	
/*	fprintf(fp, "%s %d %s %d", name1, age1, name2, age2);
	fclose(fp);*/
	
	if((fp = fopen("Yosi", "r")) == NULL){
		printf("Can't open the file\n");
	}
	printf("asd\n");
	while(1){
		fscanf(fp, "%s %d", name, &age);
		if(feof(fp)) break;
		printf(" Name = %s and age = %d\n", name, age);	
	}
			
	fclose(fp);	
	
		
}

/*#include <stdio.h>
#include <string.h>

int main() {
	FILE* 	fp = NULL;
	char 	name[128];
	int 	age;

	fp = fopen("Yosi", "w");
	if (NULL == fp) {
		return -1;
	}
	while(1) {
		printf("Please enter name anf age of a person: ");
		scanf("%s%d", name, &age);
		if (age < 1) break;
		fprintf(fp, "%s %d\n", name, age);
	}
	fclose(fp);

	fp = fopen("Yosi", "r");
	if (NULL == fp) {
		printf("Can't open file\n");
		return -1;
	}
	while(!feof(fp)) {
		fscanf(fp, "%s%d", name, &age);

		printf(" Name = %s and age = %d\n", name, age);
	}
	fclose(fp);

	return 0;
}
*/
