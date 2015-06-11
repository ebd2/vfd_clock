#include <stdlib.h>
#include <check.h>

#include "clock.h"
#include "display.h"
#include "tubechars.h"

#define MAPOVER_DIGITS(macro) \
macro(0, 0b11101000000000001010) \
macro(1, 0b00000000000000001010) \
macro(2, 0b11011000000000001000) \
macro(3, 0b10011000000000001010) \
macro(4, 0b00110000000000001010) \
macro(5, 0b10111000000000000010) \
macro(6, 0b11111000000000000010) \
macro(7, 0b00001000000000001010) \
macro(8, 0b11111000000000001010) \
macro(9, 0b10111000000000001010)
	
#define TEST_DIGIT(index, expected) \
START_TEST(test_##index) \
{ \
	uint32_t data = 0; \
	render_tubechar(&data, &tube0, DIGITS[index]); \
	ck_assert_msg(expected == data, "%d %x != %x\n", index, expected, data); \
} \
END_TEST

#define ADD_DIGIT_CASE(index, expected) \
	tcase_add_test(core, test_##index);

MAPOVER_DIGITS(TEST_DIGIT)

/*
START_TEST(test_one)
{
	uint32_t data = 0;
	render_tubechar(&data, &tube0, DIGITS[1]);
	ck_assert_int_eq(data, 0b1010);
}
END_TEST

START_TEST(test_one)
{
	uint32_t data = 0;
	render_tubechar(&data, &tube0, DIGITS[1]);
	ck_assert_int_eq(data, 0b1010);
}
END_TEST
*/

Suite *display_suite()
{
	Suite *s;
	TCase *core;

	s = suite_create("Display");
	core = tcase_create("core");

	MAPOVER_DIGITS(ADD_DIGIT_CASE)
	suite_add_tcase(s, core);

	return s;
}

int main(int argc, char *argv[])
{
	int failed;
	Suite *display;
	SRunner *sr;

	clock_init();

	display = display_suite();
	sr = srunner_create(display);

	srunner_run_all(sr, CK_NORMAL);
	failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
