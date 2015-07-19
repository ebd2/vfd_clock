#include <stdio.h>
#include "check.h"
#include "bcd_test.h"
#include "bcd.h"

void test_to_bcd_simple()
{
	ck_assert_uint_eq(0x48, to_bcd(48, 0xff));
	ck_assert_uint_eq(0x35, to_bcd(135, 0xff));
}

void test_to_bcd_mask()
{
	ck_assert_uint_eq(0x48, to_bcd(78, 0x4f));
	ck_assert_uint_eq(0x30, to_bcd(135, 0xf2));
}

void test_from_bcd_simple()
{
	ck_assert_uint_eq(48, from_bcd(0x48, 0xff));
	ck_assert_uint_eq(73, from_bcd(0x73, 0xff));
}

void test_from_bcd_mask()
{
	ck_assert_uint_eq(8, from_bcd(0x48, 0x3f));
	ck_assert_uint_eq(70, from_bcd(0x73, 0xf0));
}



Suite *bcd_suite()
{
	Suite *s;
	TCase *to_bcd;
	TCase *from_bcd;

	s = suite_create("BCD");

	to_bcd = tcase_create("to BCD");

	tcase_add_test(to_bcd, test_to_bcd_simple);
	tcase_add_test(to_bcd, test_to_bcd_mask);

	from_bcd = tcase_create("from BCD");

	tcase_add_test(from_bcd, test_from_bcd_simple);
	tcase_add_test(from_bcd, test_from_bcd_mask);

	suite_add_tcase(s, to_bcd);
	suite_add_tcase(s, from_bcd);

	return s;
}
