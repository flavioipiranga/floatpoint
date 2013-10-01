#include <embUnit/embUnit.h>
#include <gmp.h>
/*embunit:include=+ */
#include "../floatpoint.h"
/*embunit:include=- */

static void setUp(void)
{
	/* initialize */
}

static void tearDown(void)
{
	/* terminate */
}

/*embunit:impl=+ */
static void Numtofp(void)
{
	int i = 10;
	normbin nb;

	TEST_ASSERT_EQUAL_INT(1,NumToFp(&nb, "10", 1));
	TEST_ASSERT_EQUAL_INT(0,NumToFp(&nb, "12000000000000000000000000000000000000000", 1));

	//TEST_FAIL("no implementation");
}

static void Fpcmp(void)
{

	TEST_ASSERT_EQUAL_INT(-1,FpCmp("3", "10", 1));
	TEST_ASSERT_EQUAL_INT(0,FpCmp("10", "10", 1));
	TEST_ASSERT_EQUAL_INT(1,FpCmp("10", "3", 1));

	//TEST_FAIL("no implementation");
}

static void Fptonum(void)
{

	TEST_ASSERT_EQUAL_INT(15,FpToNum("01000001011100000000000000000000"));
	//TEST_ASSERT_EQUAL_INT(1,FpToNum("10", "3", 1));

	//TEST_FAIL("no implementation");
}

static void Sum(void)
{

	TEST_ASSERT_EQUAL_INT(20,Add("10", "10", 1));
	TEST_ASSERT_EQUAL_INT(5,Add("2.5", "2.5", 1));

	//TEST_ASSERT_EQUAL_INT(1,FpToNum("10", "3", 1));

	//TEST_FAIL("no implementation");
}

static void Subtract(void)
{

	TEST_ASSERT_EQUAL_INT(5,Sub("10", "5", 1));
	TEST_ASSERT_EQUAL_INT(5,Sub("7.5", "2.5", 1));
}

static void Simpletodouble(void)
{
	normbin nb;

	TEST_ASSERT_EQUAL_INT(1,SimpleFpToDoubleFp(nb, "01000001101000000000000000000000"));
}


/*embunit:impl=- */
TestRef embunit_tests(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		/*embunit:fixtures=+ */
		new_TestFixture("NumToFp",Numtofp),
				new_TestFixture("NumToFp",Fpcmp),
				new_TestFixture("FpToNum",Fptonum),
				new_TestFixture("Add",Sum),
				new_TestFixture("Sub",Subtract),



				/*embunit:fixtures=- */
	};
	EMB_UNIT_TESTCALLER(embunit,"embunit",setUp,tearDown,fixtures);
	return (TestRef)&embunit;
};
