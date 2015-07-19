#include "DS1307.h"
#include "bcd.h"
#include "i2c.h"

#define DS1307_SLA 0b1101000

#define TEST_STATUS_AND_ABORT(expected, actual) \
	do { \
		uint8_t _status_ = (actual); \
		if (_status_ != (expected)) { \
			goto out; \
		} \
	} while(0);

uint8_t DS1307_is_enabled(uint8_t *enabled)
{
	uint8_t status;
	uint8_t seconds;

	if ((status = DS1307_read(&seconds, 1, 0x0))) {
		goto out;
	}

	*enabled = !(seconds & 0x80);
out:
	return status;
}

uint8_t DS1307_enable(uint8_t *enabled)
{
	uint8_t second = 0;
	return DS1307_write(&second, 0x0, 1);
}

uint8_t DS1307_disable(uint8_t *enabled)
{
	uint8_t second = 0x80;
	return DS1307_write(&second, 0x0, 1);
}

uint8_t DS1307_read(uint8_t *dest, uint8_t addr, uint8_t len)
{
	uint8_t status;
	uint8_t i;

	TEST_STATUS_AND_ABORT(TW_START, i2c_start());
	TEST_STATUS_AND_ABORT(TW_MT_SLA_ACK, i2c_sla(DS1307_SLA, TW_WRITE));
	TEST_STATUS_AND_ABORT(TW_MT_DATA_ACK, i2c_write(addr));
	TEST_STATUS_AND_ABORT(TW_REP_START, i2c_start());
	TEST_STATUS_AND_ABORT(TW_MR_SLA_ACK, i2c_sla(DS1307_SLA, TW_READ));

	for (i = 0; i < len - 1; ++i) {
		TEST_STATUS_AND_ABORT(TW_MR_DATA_ACK, i2c_read_ack(dest + i));
	}
	TEST_STATUS_AND_ABORT(TW_MR_DATA_NACK, i2c_read_nack(dest + i));

	status = 0;
out:
	i2c_stop();
	return status;
}

uint8_t DS1307_write(uint8_t *data, uint8_t addr, uint8_t len)
{
	uint8_t status;
	uint8_t i;

	TEST_STATUS_AND_ABORT(TW_START, i2c_start());
	TEST_STATUS_AND_ABORT(TW_MT_SLA_ACK, i2c_sla(DS1307_SLA, TW_WRITE));
	TEST_STATUS_AND_ABORT(TW_MT_DATA_ACK, i2c_write(addr));

	for(i = 0; i < len; ++i) {
		TEST_STATUS_AND_ABORT(TW_MT_DATA_ACK, i2c_write(data[i]));
	}

	status = 0;
out:
	i2c_stop();
	return status;
}

uint8_t DS1307_read_time(uint16_t century, DS1307_tm_t *tm)
{
	uint8_t status;
	uint8_t time[7];

	if ((status = DS1307_get_time(time))) {
		goto out;
	}

	DS1307_from_raw_time(century, tm, time);
out:
	return status;
}

uint8_t DS1307_write_time(uint16_t century, DS1307_tm_t *tm)
{
	uint8_t status = 0;
	uint8_t time[7];

	DS1307_to_raw_time(time, century, tm);

	status = DS1307_set_time(time);
	return status;
}

void DS1307_to_raw_time(uint8_t raw_time[7], uint16_t century,
		DS1307_tm_t *tm)
{
	raw_time[0] = to_bcd(tm->tm_sec, 0x7f);
	raw_time[1] = to_bcd(tm->tm_min, 0x7f);
	if (tm->tm_hour_mode == HOUR_MODE_12) {
		raw_time[2] = to_bcd(tm->tm_hour, 0x1f);
		raw_time[2] |= HOUR_MODE_FLAG;
		raw_time[2] |= tm->tm_am_pm ? 0 : PM_FLAG;
	} else {
		raw_time[2] = to_bcd(tm->tm_hour, 0x3f);
	}

	// add 1 to convert from standard stuct tm usage to DS1307 convention.
	raw_time[3] = to_bcd(tm->tm_wday + 1, 0x7);

	raw_time[4] = to_bcd(tm->tm_mday, 0x3f);
	raw_time[5] = to_bcd(tm->tm_mon, 0x1f);
	raw_time[6] = to_bcd(tm->tm_year - century * 100, 0xff);
}	

void DS1307_from_raw_time(uint16_t century, DS1307_tm_t *tm,
		uint8_t raw_time[7])
{
	uint8_t h;

	tm->tm_sec = from_bcd(raw_time[0], 0x7f);
	tm->tm_min = from_bcd(raw_time[1], 0x7f);

	h = raw_time[2];
	if (h & HOUR_MODE_FLAG) {
		tm->tm_hour_mode = HOUR_MODE_12;
		tm->tm_hour = from_bcd(h, 0x1f);
		tm->tm_am_pm = (h & PM_FLAG) ? PM : AM;
	} else {
		tm->tm_hour_mode = HOUR_MODE_24;
		tm->tm_hour = from_bcd(h, 0x3f);
	}
	
	// subtract 1 to bring weekday in line with standard struct tm.
	tm->tm_wday = from_bcd(raw_time[3], 0x7) - 1;

	tm->tm_mday = from_bcd(raw_time[4], 0x3f);
	tm->tm_mon = from_bcd(raw_time[5], 0x1f);
	tm->tm_year = from_bcd(raw_time[6], 0xff) + century * 100;
}
