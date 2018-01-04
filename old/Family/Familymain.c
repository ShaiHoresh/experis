#include <stdio.h>

typedef int (*Profession )(char*) ;

typedef struct{
	char* name;
	int age;
	Profession func;
} person;



struct familyTree {
	int nMembers;
	person p[2];
	struct familyTree* next;
};

typedef struct familyTree FamilyTree_t;

int Refua(char* name)
{
    printf("I'm a doctor\n");
    return 0;
}

int Handasa(char* name) { printf("Trust me, I'm an engineer\n"); return 0; }

FamilyTree_t Halakhmi = {2, "Ilan", 28, Handasa, "Gilad", 26, Refua, 0};
FamilyTree_t Levi     = {2, "David", 38, Refua, "Lea", 30, Handasa, 0};

void DoIt(FamilyTree_t* ftPtr, char* name) {
	if(strcmp(ftPtr->p[0].name, name) == 0)
	{
	    ftPtr->p[0].func("Yosi");
    }
    else if(strcmp(ftPtr->p[1].name, name) == 0)
    {
	    ftPtr->p[1].func(name);
    }
	
}
int main() 
{
	DoIt(&Halakhmi, "Ilan");
	DoIt(&Levi, "David");
	
	return 1;
}

