#include </Users/flavioipiranga/Downloads/embunit/embUnit/embUnit.h>
#include <gmp.h>
/*embunit:extern=+ */
extern TestRef embunit_tests(void);
/*embunit:extern=- */

int main(int argc,char *argv[])
{
	TestRunner_start();
	/*embunit:run=+ */
		TestRunner_runTest(embunit_tests());
	/*embunit:run=- */
	TestRunner_end();
	return 0;
}
