typedef int (* Profession )(char*) ;

typedef struct{
	char* name;
	int age;
	Profession func;
} person;



struct familyTree {
	int nMembers;
	person p[2];
	struct familyTree* next;
/* 2 only for example, has to be person* p; */
/* points to another family */
/* all members of a family have the same proffesion */
};

typedef struct familyTree FamilyTree_t;



