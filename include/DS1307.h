#ifndef DS1307_H
#define DS1307_H

#include <stdint.h>
#include <time.h>

#include <util/twi.h>

#define DS1307_CR_ADDR 0x7
#define DS1307_CR_SIZE 1

#define DS1307_TIME_ADDR 0x0
#define DS1307_TIME_SIZE 7

#define HOUR_MODE_FLAG 0x40
#define PM_FLAG 0x20

typedef enum hour_mode {
	HOUR_MODE_24 = 0,
	HOUR_MODE_12,
} hour_mode_t;

typedef enum am_pm {
	AM = 0,
	PM,
} am_pm_t;

/*
 * With the exceptions noted below, the fields in this struct correspond to
 * the fields with the same name in the standard struct tm in time.h.
 */
typedef struct DS1307_tm {
	int8_t tm_sec;
	int8_t tm_min;
	/*
	 * tm_hour may be in 12 or 24 hour format based on the setting of the
	 * DS1307.  The tm_hour_mode and tm_am_pm fields indicate whether the
	 * DS1307 is in 12 or 24 hour mode and, if in 12 hour mode, whether the
	 * tm_hour field is AM or PM.
	 */
	int8_t tm_hour;

	int8_t tm_mday;

	/*
	 * The DS1307 uses the range [1,7] to represent weekdays rather than [0,6]
	 * for the standard struct tm.  This field should be used per the standard.
	 * DS1307_read_time and DS1307_write_time will handle the conversion.
	 */
	int8_t tm_wday;
	int8_t tm_mon;

	/*
	 * Because we didn't learn our lesson in 1999, the DS1307 deals in 2 digit
	 * years.  Aaargh.  The century argument to DS1307_read/write_time is used
	 * to convert the 2 digit year to/from a 4 digit year.
	 */
	int16_t tm_year;
	hour_mode_t tm_hour_mode;
	am_pm_t tm_am_pm;
} DS1307_tm_t;

uint8_t DS1307_is_enabled();
uint8_t DS1307_enable();
uint8_t DS1307_disable();

/*
 * Low-level routines to read/write data from/to the RAM in the DS1307
 */
uint8_t DS1307_read(uint8_t *dest, uint8_t addr, uint8_t len);
uint8_t DS1307_write(uint8_t *data, uint8_t addr, uint8_t len);

/*
 * Convenience macros to handle common read/write addresses and sizes.
 */
#define DS1307_get_CR(value) \
	DS1307_read(value, DS1307_CR_ADDR, DS1307_CR_SIZE)

#define DS1307_set_CR(value) \
	DS1307_write(value, DS1307_CR_ADDR, DS1307_CR_SIZE)

#define DS1307_get_time(value) \
	DS1307_read(value, DS1307_TIME_ADDR, DS1307_TIME_SIZE)

#define DS1307_set_time(value) \
	DS1307_write(value, DS1307_TIME_ADDR, DS1307_TIME_SIZE)

/*
 * High level routines to set and get the time in human readable format.
 */
uint8_t DS1307_read_time(uint16_t century, DS1307_tm_t *tm);
uint8_t DS1307_write_time(uint16_t century, DS1307_tm_t *tm);

/*
 * Functions to convert between the raw time data the DS1307 sends/receives and
 * human readable format.
 */
void DS1307_to_raw_time(uint8_t raw_time[7], uint16_t century,
		DS1307_tm_t *tm);
void DS1307_from_raw_time(uint16_t century, DS1307_tm_t *tm,
		uint8_t raw_time[7]);

#endif
