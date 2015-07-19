#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "DS1307_test.h"
#include "display_test.h"
#include "bcd_test.h"

typedef Suite *(*suite_provider)();

suite_provider suite_providers[] = {
	DS1307_suite,
	display_suite,
	bcd_suite,
};

int main(int argc, char *argv[])
{
	int failed = 0;
	int i;

	for (i = 0; i < sizeof(suite_providers)/sizeof(suite_providers[0]); ++i) {
		Suite *suite;
		SRunner *runner;

		suite = suite_providers[i]();

		runner = srunner_create(suite);

		srunner_run_all(runner, CK_NORMAL);
		failed += srunner_ntests_failed(runner);
		srunner_free(runner);
	}
	return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
