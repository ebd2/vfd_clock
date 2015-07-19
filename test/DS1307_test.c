#include<check.h>

#include "DS1307.h"

static void assert_raw_time_equal(uint8_t actual[7], uint8_t expected[7],
		const char *test_name)
{
	int i;
	for (i = 0; i < 7; ++i) {
		ck_assert_msg(actual[i] == expected[i], "Mismatch in test %s: "
				"actual[%d] = %x, expected[%d] = %x", test_name, i, actual[i],
				i, expected[i]);
	}
}

void test_to_raw_am()
{
	DS1307_tm_t tm = {
		30,
		15,
		8,

		10,
		6,
		4,
		2010,

		HOUR_MODE_12,
		AM,
	};

	uint8_t expected[7] = {
		0x30, 0x15, 0x48, 0x7, 0x10, 0x4, 0x10
	};

	uint8_t actual[7];

	DS1307_to_raw_time(actual, 20, &tm);

	assert_raw_time_equal(actual, expected, __FUNCTION__);
}

void test_to_raw_pm()
{
	DS1307_tm_t tm = {
		45,
		30,
		12,

		10,
		6,
		4,
		2010,

		HOUR_MODE_12,
		PM,
	};

	uint8_t expected[7] = {
		0x45, 0x30, 0x72, 0x7, 0x10, 0x4, 0x10
	};

	uint8_t actual[7];

	DS1307_to_raw_time(actual, 20, &tm);

	assert_raw_time_equal(actual, expected, __FUNCTION__);
}

void test_to_raw_24h()
{
	DS1307_tm_t tm = {
		17,
		45,
		17,

		10,
		6,
		4,
		2010,

		HOUR_MODE_24,
		PM,
	};

	uint8_t expected[7] = {
		0x17, 0x45, 0x17, 0x7, 0x10, 0x4, 0x10
	};

	uint8_t actual[7];

	DS1307_to_raw_time(actual, 20, &tm);

	assert_raw_time_equal(actual, expected, __FUNCTION__);
}

static void assert_DS1307_tm_equal(DS1307_tm_t *actual, DS1307_tm_t *expected,
		const char *test_name)
{
#define ASSERT_MEMBER_EQUAL(memb_name, human_name) \
	ck_assert_msg(actual->memb_name == expected->memb_name, \
			"%s mismatch in test %s.  expected %d, actual %d", human_name, \
			test_name, expected->memb_name, actual->memb_name);

	ASSERT_MEMBER_EQUAL(tm_sec, "Seconds");
	ASSERT_MEMBER_EQUAL(tm_min, "Minutes");
	ASSERT_MEMBER_EQUAL(tm_hour, "Hours");
	ASSERT_MEMBER_EQUAL(tm_mday, "Day of month");
	ASSERT_MEMBER_EQUAL(tm_wday, "Day of week");
	ASSERT_MEMBER_EQUAL(tm_mon, "Month");
	ASSERT_MEMBER_EQUAL(tm_year, "Year");
	ASSERT_MEMBER_EQUAL(tm_hour_mode, "Hour mode");

	if(expected->tm_hour_mode == HOUR_MODE_12) {
		ASSERT_MEMBER_EQUAL(tm_am_pm, "AM/PM");
	}

#undef ASSERT_MEMBER_EQUAL
}

void test_from_raw_am()
{
	uint8_t raw_time[7] = { 0x0, 0x15, 0x52, 0x2, 0x27, 0x9, 0x10 };

	DS1307_tm_t expected = {
		0,
		15,
		12,
		27,
		1,
		9,
		2010,
		HOUR_MODE_12,
		AM,
	};

	DS1307_tm_t actual;

	DS1307_from_raw_time(20, &actual, raw_time);

	assert_DS1307_tm_equal(&actual, &expected, __FUNCTION__);
}

void test_from_raw_pm()
{
	uint8_t raw_time[7] = { 0x56, 0x22, 0x71, 0x2, 0x27, 0x9, 0x10 };

	DS1307_tm_t expected = {
		56,
		22,
		11,
		27,
		1,
		9,
		2010,
		HOUR_MODE_12,
		PM,
	};

	DS1307_tm_t actual;

	DS1307_from_raw_time(20, &actual, raw_time);

	assert_DS1307_tm_equal(&actual, &expected, __FUNCTION__);
}

void test_from_raw_24h()
{
	uint8_t raw_time[7] = { 0x37, 0x43, 0x6, 0x2, 0x27, 0x9, 0x10 };

	DS1307_tm_t expected = {
		37,
		43,
		6,
		27,
		1,
		9,
		2010,
		HOUR_MODE_24,
		PM,
	};

	DS1307_tm_t actual;

	DS1307_from_raw_time(20, &actual, raw_time);

	assert_DS1307_tm_equal(&actual, &expected, __FUNCTION__);
}

Suite *DS1307_suite()
{
	Suite *s;
	TCase *to_raw_time;
	TCase *from_raw_time;

	s = suite_create("DS1307");
	to_raw_time = tcase_create("to_raw_time");

	tcase_add_test(to_raw_time, test_to_raw_am);
	tcase_add_test(to_raw_time, test_to_raw_pm);
	tcase_add_test(to_raw_time, test_to_raw_24h);

	from_raw_time = tcase_create("from_raw_time");

	tcase_add_test(from_raw_time, test_from_raw_am);
	tcase_add_test(from_raw_time, test_from_raw_pm);
	tcase_add_test(from_raw_time, test_from_raw_24h);

	suite_add_tcase(s, to_raw_time);
	suite_add_tcase(s, from_raw_time);
	return s;
}
