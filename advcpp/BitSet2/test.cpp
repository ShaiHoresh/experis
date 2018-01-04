#include "BitSet.h"
#include "mu_test.h"
#include <iostream>

using namespace advcpp;



/* ============================= 	*/	
UNIT(create_from_bool_array)

	bool arr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = false;
	}	
	BitSet<100, unsigned int> set(arr);
	
	ASSERT_THAT(1);
END_UNIT
/* ============================= 	*/	
UNIT(is_on)

	bool arr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = false;
	}	
	BitSet<100, unsigned int> set(arr);

	for (int i = 0; i < 99; i+=2)
	{
		ASSERT_THAT(set[i]);
		ASSERT_THAT(!set[i+1]);
	}	
END_UNIT
/* ============================= 	*/	
UNIT(set)

	bool arr[100];
	
	for (int i = 0; i < 100; i++)
	{
		arr[i] = true;
	}	
	
	BitSet<100, unsigned int> set(arr);

	for (int i = 0; i < 100; i++)
	{
		ASSERT_THAT(set[i]);
	}	

	for (int i = 0; i < 100; i++)
	{
		set[i] = false;
	}		

	for (int i = 0; i < 100; i++)
	{
		ASSERT_THAT(!set[i]);
	}		
	
END_UNIT
/* ============================= 	*/	
UNIT(subscripit_assigment)

	bool arr[100];
	
	for (int i = 0; i < 100; i++)
	{
		arr[i] = true;
	}	
	
	BitSet<100, unsigned int> set(arr);

	for (int i = 0; i < 100; i++)
	{
		ASSERT_THAT(set[i]);
	}	

	for (int i = 0; i < 100; i++)
	{
		set[i] = false;
	}		

	for (int i = 0; i < 100; i++)
	{
		ASSERT_THAT(!set[i]);
	}		
	
END_UNIT
/* ============================= 	*/	
UNIT(subscript_value)

	bool arr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = false;
	}	
	
	BitSet<100, unsigned int> set(arr);

	for (int i = 0; i < 99; i+=2)
	{
		ASSERT_THAT(set[i]);
		ASSERT_THAT(!set[i+1]);
	}	
END_UNIT
/* ============================= 	*/
UNIT(count)

	bool arr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = false;
	}	
	
	BitSet<100, unsigned int> set(arr);
	ASSERT_THAT(50 == set.Count());
END_UNIT	
/* ============================= 	*/
UNIT(any_when_not)

	bool arr[100];
	
	for (int i = 0; i < 100; i++)
	{
		arr[i] = false;
	}	
	
	BitSet<100, unsigned int> set(arr);

	ASSERT_THAT(!set.Any());
END_UNIT		
/* ============================= 	*/
UNIT(any_when_there_is)

	bool arr[100];
	
	for (int i = 0; i < 99; i++)
	{
		arr[i] = false;
	}	
	arr[99] = true;
	BitSet<100, unsigned int> set(arr);

	ASSERT_THAT(set.Any());
END_UNIT	
/* ============================= 	*/	
UNIT(all_when_not)

	bool arr[100];
	
	for (int i = 0; i < 99; i++)
	{
		arr[i] = true;
	}	
	arr[99] = false;
	BitSet<100, unsigned int> set(arr);

	ASSERT_THAT(!set.All());
END_UNIT	
/* ============================= 	*/	
UNIT(all_when_true)

	bool arr[100];
	
	for (int i = 0; i < 100; i++)
	{
		arr[i] = true;
	}	
	BitSet<100, unsigned int> set(arr);

	ASSERT_THAT(set.All());
END_UNIT	
/* ============================= 	*/
UNIT(none_when_not)

	bool arr[100];
	
	for (int i = 0; i < 100; i++)
	{
		arr[i] = false;
	}	
	
	arr[64] = true;
	BitSet<100, unsigned int> set(arr);

	ASSERT_THAT(!set.None());
END_UNIT		
/* ============================= 	*/
UNIT(none_when_true)

	bool arr[100];
	
	for (int i = 0; i < 100; i++)
	{
		arr[i] = false;
	}	

	BitSet<100, unsigned int> set(arr);

	ASSERT_THAT(set.None());
END_UNIT	
/* ============================= 	*/	
UNIT(operator_or)

	bool arr1[100];
	bool arr2[100];
	bool retArr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr1[i] = true;
		arr1[i+1] = false;

		arr2[i] = false;		
		arr2[i+1] = true;
		
		retArr[i] = false;		
		retArr[i+1] = false;
	}		

	BitSet<100, unsigned int> set1(arr1);
	BitSet<100, unsigned int> set2(arr2);
	BitSet<100, unsigned int> ret(retArr);
	ret = set1 | set2;
	ASSERT_THAT(ret.All());
END_UNIT
/* ============================= 	*/	
UNIT(operator_assigment_or)

	bool arr1[100];
	bool arr2[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr1[i] = true;
		arr1[i+1] = false;

		arr2[i] = false;		
		arr2[i+1] = true;
	}		

	BitSet<100, unsigned int> set1(arr1);
	BitSet<100, unsigned int> set2(arr2);
	set1 |= set2;
	ASSERT_THAT(set1.All());
END_UNIT	
/* ============================= 	*/	
UNIT(operator_and)

	bool arr1[100];
	bool arr2[100];
	bool retArr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr1[i] = true;
		arr1[i+1] = false;

		arr2[i] = false;		
		arr2[i+1] = true;
		
		retArr[i] = false;		
		retArr[i+1] = false;
	}		

	BitSet<100, unsigned int> set1(arr1);
	BitSet<100, unsigned int> set2(arr2);
	BitSet<100, unsigned int> ret(retArr);
	ret = set1 & set2;
	ASSERT_THAT(ret.None());
END_UNIT
/* ============================= 	*/	
UNIT(operator_assigment_and)

	bool arr1[100];
	bool arr2[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr1[i] = true;
		arr1[i+1] = false;

		arr2[i] = false;		
		arr2[i+1] = true;
	}		

	BitSet<100, unsigned int> set1(arr1);
	BitSet<100, unsigned int> set2(arr2);
	set1 &= set2;
	ASSERT_THAT(set1.None());
END_UNIT
/* ============================= 	*/	
UNIT(operator_xor)

	bool arr1[100];
	bool arr2[100];
	bool retArr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr1[i] = true;
		arr1[i+1] = false;

		arr2[i] = true;		
		arr2[i+1] = true;
		
		retArr[i] = false;		
		retArr[i+1] = false;
	}		

	BitSet<100, unsigned int> set1(arr1);
	BitSet<100, unsigned int> set2(arr2);
	BitSet<100, unsigned int> ret(retArr);
	ret = set1 ^ set2;
	
	ASSERT_THAT(50 == ret.Count());
END_UNIT
/* ============================= 	*/	
UNIT(operator_assigment_xor)

	bool arr1[100];
	bool arr2[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr1[i] = true;
		arr1[i+1] = false;

		arr2[i] = true;		
		arr2[i+1] = true;
	}		

	BitSet<100, unsigned int> set1(arr1);
	BitSet<100, unsigned int> set2(arr2);
	set1 ^= set2;
	ASSERT_THAT(50 == set1.Count());
END_UNIT		
/* ============================= 	*/	
UNIT(operator_tilda)

	bool arr[100];
	bool retArr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = false;
		
		retArr[i] = false;		
		retArr[i+1] = false;
	}		

	BitSet<100, unsigned int> set(arr);
	BitSet<100, unsigned int> ret(retArr);
	ret = ~set;
	ASSERT_THAT(50 == ret.Count());
END_UNIT
/* ============================= 	*/	
UNIT(flip)

	bool arr1[100];
	
	for (int i = 0; i < 100; ++i)
	{
		arr1[i] = true;
	}		

	BitSet<100, unsigned int> set1(arr1);
	set1.Flip();
	ASSERT_THAT(set1.None());
END_UNIT

/* ============================= 	*/	
UNIT(operator_left_shift)

	bool arr[100];
	bool retArr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = true;
		
		retArr[i] = false;		
		retArr[i+1] = false;
	}		

	BitSet<100, unsigned int> set(arr);
	BitSet<100, unsigned int> ret(retArr);
	ret = set << 10;
	for(int i = 0; i < 10; ++i)
	{
		ASSERT_THAT(ret[i] == false);	
	}
	ASSERT_THAT(90 == ret.Count());
		
END_UNIT
/* ============================= 	*/	
UNIT(operator_assigment_left_shift)

	bool arr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = true;
	}		

	BitSet<100, unsigned int> set(arr);
	set <<= 10;
	for(int i = 0; i < 10; ++i)
	{
		ASSERT_THAT(set[i] == false);	
	}
	ASSERT_THAT(90 == set.Count());
END_UNIT
/* ============================= 	*/	
UNIT(operator_right_shift)

	bool arr[100];
	bool retArr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = true;
		
		retArr[i] = false;		
		retArr[i+1] = false;
	}		

	BitSet<100, unsigned int> set(arr);
	BitSet<100, unsigned int> ret(retArr);
	ret = set >> 10;

	for(int i = 90; i < 100; ++i)
	{
		ASSERT_THAT(ret[i] == false);	
	}
	
	ASSERT_THAT(90 == ret.Count());
END_UNIT
/* ============================= 	*/	
UNIT(operator_assigment_right_shift)

	bool arr[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		arr[i] = true;
		arr[i+1] = true;
	}		

	BitSet<100, unsigned int> set(arr);
	set >>= 10;
	for(int i = 90; i < 100; ++i)
	{
		ASSERT_THAT(set[i] == false);	
	}
	ASSERT_THAT(90 == set.Count());

END_UNIT

/* ============================= 	*/	
UNIT(operator_equal_when_true)
	bool first[100];
	bool sec[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		first[i] = true;
		first[i+1] = false;
		
		sec[i] = true;		
		sec[i+1] = false;
	}		

	BitSet<100, unsigned int> firstS(first);
	BitSet<100, unsigned int> secS(sec);
	ASSERT_THAT(firstS == secS);
END_UNIT
/* ============================= 	*/	
UNIT(operator_equal_when_false)
	bool first[100];
	bool sec[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		first[i] = true;
		first[i+1] = false;
		
		sec[i] = false;		
		sec[i+1] = true;
	}		

	BitSet<100, unsigned int> firstS(first);
	BitSet<100, unsigned int> secS(sec);

	ASSERT_THAT(!(firstS == secS));
END_UNIT
/* ============================= 	*/	
UNIT(operator_not_equal_when_true)
	bool first[100];
	bool sec[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		first[i] = true;
		first[i+1] = false;
		
		sec[i] = false;		
		sec[i+1] = true;
	}		

	BitSet<100, unsigned int> firstS(first);
	BitSet<100, unsigned int> secS(sec);

	ASSERT_THAT((firstS != secS));
END_UNIT
/* ============================= 	*/	
UNIT(operator_not_equal_when_false)
	bool first[100];
	bool sec[100];
	
	for (int i = 0; i < 99; i+=2)
	{
		first[i] = true;
		first[i+1] = false;
		
		sec[i] = true;		
		sec[i+1] = false;
	}		

	BitSet<100, unsigned int> firstS(first);
	BitSet<100, unsigned int> secS(sec);

	ASSERT_THAT(!(firstS != secS));
END_UNIT
/* ============================= 	*/
/*			TEST SUIT				*/
/* ============================= 	*/	

TEST_SUITE(BitSet)

	TEST(create_from_bool_array)
	TEST(is_on)
	TEST(set)
	TEST(subscripit_assigment)		
	TEST(subscript_value)		
	TEST(count)		
	TEST(any_when_not)			
	TEST(any_when_there_is)	
	TEST(all_when_not)
	TEST(all_when_true)
	TEST(none_when_not)
	TEST(none_when_true)	
	TEST(operator_or)
	TEST(operator_assigment_or)	
	TEST(operator_and)
	TEST(operator_assigment_and)	
	TEST(operator_xor)
	TEST(operator_assigment_xor)	
	TEST(operator_tilda)	
	TEST(flip)
	TEST(operator_left_shift)
	TEST(operator_assigment_left_shift)	
	TEST(operator_right_shift)
	TEST(operator_assigment_right_shift)		
	TEST(operator_equal_when_true)
	TEST(operator_equal_when_false)
	TEST(operator_not_equal_when_true)
	TEST(operator_not_equal_when_false)		
END_SUITE


