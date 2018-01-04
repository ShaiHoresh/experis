#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGH 64

int main(){

	char name[MAX_NAME_LENGH];
	int age, nLng;
/*	int nBytes, bBytes;*/
	FILE* fp = NULL;
	
	fp = fopen("Yosi", "w");
	if (NULL == fp) {
		return -1;
	}
	while(1) {
		printf("Please enter name anf age of a person: ");
		scanf("%s%d", name, &age);
		if (age < 1) break;
		nLng = strlen(name) + 1;
		fwrite(&nLng, sizeof(int), 1, fp);
/*		nBytes = */fwrite(name, 1, nLng, fp);
/*		bBytes = */fwrite(&age, sizeof(int), 1, fp);
	}
	fclose(fp);
	

	if((fp = fopen("Yosi", "r")) == NULL){
		printf("Can't open the file\n");
	}
	
	while(1){
		fread(&nLng, sizeof(int), 1, fp);
		fread(name, 1, nLng, fp);
        fread(&age, sizeof(int), 1, fp);
		if(feof(fp)) break;
	}
			
	fclose(fp);	
	
	return 0;
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
