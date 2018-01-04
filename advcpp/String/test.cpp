#include <string.h> // strcmp, strcpy
#include <stdexcept>
#include "mu_test.h"
#include "String.h"
#include <iostream>


using namespace advcpp;

/* ============================= 	*/
/*				TESTS				*/
/* ============================= 	*/	
UNIT(DEF_CTOR)
	String createdString;
	
	ASSERT_THAT(strcmp(createdString.Get_c_Str(), "") == 0);

END_UNIT
/* ============================= 	*/
UNIT(CTOR_from_char_ptr)
	char str[32];
	
	strcpy(str, "like dis");
	String string(str);
	
	ASSERT_THAT(strcmp(string.Get_c_Str(), "like dis") == 0);
	
	String anotherString("like dat");
	
	ASSERT_THAT(strcmp(anotherString.Get_c_Str(), "like dat") == 0);
	
END_UNIT
/* ================================= */
//UNIT(CTOR_from_null_cp)
	
//	bool caught = false;
//	
//	try
//	{
//		String string(0);
//	}	
//	
//	catch (std::invalid_argument)
//	{
//		caught = true; 
//	}
//	
//	ASSERT_THAT(caught);
	
//END_UNIT
/* ============================= 	*/
UNIT(copy_CTOR)
	String first("dis is string");
	
	String second(first);
	
	ASSERT_THAT(strcmp(second.Get_c_Str(), "dis is string") == 0);
END_UNIT
/* ============================= 	*/
UNIT(Assignment)
	String first("dis is string");
	
	String second;
	
	second = first;
	
	ASSERT_THAT(strcmp(second.Get_c_Str(), "dis is string") == 0);
	
	second = "and now?";
	
	ASSERT_THAT(strcmp(second.Get_c_Str(), "and now?") == 0);
END_UNIT
/* ============================= 	*/
UNIT(Length)
	String str55;
	
	ASSERT_THAT(str55.Length() == 0);

	str55 = "STRING WITH 20 CHARS";

	ASSERT_THAT(str55.Length() == 20);
END_UNIT

/* ============================= 	*/	
UNIT(ToUpper)
	String str("I wan7t tO te~st s8Um StufF=");
	
	str.ToUpper();
 
 	ASSERT_THAT(strcmp(str.Get_c_Str(), "I WAN7T TO TE~ST S8UM STUFF=") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(ToLower)
	String str("I wan7t tO te~st s8Um StufF=");
	
	str.ToLower();
    
	ASSERT_THAT(strcmp(str.Get_c_Str(), "i wan7t to te~st s8um stuff=") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(plus_char_ptr)
	String str("we comple");
	
	str = str + "te each other";
	
	ASSERT_THAT(strcmp(str.Get_c_Str(), "we complete each other") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(plus_String)
	String beg("we comple");
	String end("te each other");
	
	beg = beg + end;
	
	ASSERT_THAT(strcmp(beg.Get_c_Str(), "we complete each other") == 0);
END_UNIT
/* ============================= 	*/	
UNIT(Comparators)
	String string("string");
	String Identical("string");
	String Different("different");
	
	ASSERT_THAT(string == Identical);
	ASSERT_THAT(string != Different);
	ASSERT_THAT(!(string != Identical));
	ASSERT_THAT(!(string == Different));
	ASSERT_THAT(string == "string");
	ASSERT_THAT(string != "not");
	ASSERT_THAT(!(string == "not"));
	ASSERT_THAT(!(string != "string"));	
	
END_UNIT

/* ============================= 	*/	
UNIT(GetIndexth)
	unsigned int i;
	String str("0123456789");
	
	for (i = 0; i < str.Length(); i += 1)
	{
		ASSERT_THAT(str[i] == i + '0');
	}
	
END_UNIT
/* ================================= */
UNIT(GetIndexthOutOfBound)

	bool caught = false;
	
	String tenDigits("0123456789");
	
	try
	{
		tenDigits[10];
	}
	
	catch(std::out_of_range)
	{
		caught = true;
	}
	
	ASSERT_THAT(caught);
	
END_UNIT
/* ============================= 	*/
/*			TEST SUIT				*/
/* ============================= 	*/	

TEST_SUITE(String)
	TEST(DEF_CTOR)
	TEST(CTOR_from_char_ptr)
//	TEST(CTOR_from_null_cp)
	TEST(copy_CTOR)
	TEST(Assignment)
	TEST(Length)
	TEST(ToUpper)
	TEST(ToLower)
	TEST(plus_char_ptr)
	TEST(plus_String)
	TEST(Comparators)
	TEST(GetIndexth)
	TEST(GetIndexthOutOfBound)
END_SUITE
