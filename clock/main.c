#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <string.h>

#include "clock.h"
#include "display.h"
#include "tubechars.h"
#include "DS1307.h"

void ioinit (void)
{
	//1 = output, 0 = input
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
}

void count()
{
	uint32_t c_data;
	uint8_t i;

	c_data = 0xfffff;
	tube0.grid->c_data = c_data;
	_delay_ms(1000.0);

	c_data = 0;
	tube0.grid->c_data = c_data;
	_delay_ms(1000.0);

	for (i = 0; i < DIGITS_LEN; ++i) {
		c_data = 0;
		render_tubechar(&c_data, &tube0, DIGITS[i]);
		tube0.grid->c_data = c_data;
		_delay_ms(1000.0);
	}

	for (i = 0; i < LETTERS_LEN; ++i) {
		c_data = 0;
		render_tubechar(&c_data, &tube0, LETTERS[i]);
		tube0.grid->c_data = c_data;
		_delay_ms(1000.0);
	}
}

void show_byte(uint8_t b)
{
	char disp[3];
	uint8_t n;

	disp[2] = 0;

	n = b & 0xf;
	if (n < 10) {
		disp[1] = '0' + n;
	} else {
		disp[1] = 'a' + n - 10;
	}
		
	n = (b >> 4)  & 0xf;
	if (n < 10) {
		disp[0] = '0' + n;
	} else {
		disp[0] = 'a' + n - 10;
	}

	say(&clock_display, disp);
}

int main()
{
	clock_init();
	ioinit();
	sei();

	uint8_t before, after;
	uint8_t cr = 0x10;

	if (!DS1307_is_enabled()) {
		DS1307_enable();
	}

	DS1307_get_CR(&before);
	DS1307_set_CR(&cr);
	DS1307_get_CR(&after);

	/*
	DS1307_read_time();
	DS1307_read_time();
	DS1307_write_time(2015, 7, 7, 2, );
	*/

	show_byte(before);
	show_byte(after);
	/*
	_delay_ms(5000.0);
	DS1307_disable();
	*/

	for(;;) {
		PORTC = 0xFF;
		_delay_ms(500.0);
		PORTC = 0x0;
		_delay_ms(500.0);
	}
}
