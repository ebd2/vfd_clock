#include <avr/io.h>
#include "i2c.h"

// Mask of prescaler bits when returning statuses.
#define TW_STATUS_MASK 0xf8

uint8_t i2c_start()
{
	// enable TWI, send start, clear interrupt.
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	while (!(TWCR & _BV(TWINT)));
	return TWSR & TW_STATUS_MASK;
}

uint8_t i2c_sla(uint8_t addr, uint8_t rw)
{
	TWDR = addr << 1 | rw;
	TWCR = _BV(TWINT) | _BV(TWEN);

	while (!(TWCR & _BV(TWINT)));
	return TWSR & TW_STATUS_MASK;
}

uint8_t i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);

	while (!(TWCR & _BV(TWINT)));
	return TWSR & TW_STATUS_MASK;
}

uint8_t i2c_read_ack(uint8_t *data)
{
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	while (!(TWCR & _BV(TWINT)));
	*data = TWDR;
	return TWSR & TW_STATUS_MASK;
}

uint8_t i2c_read_nack(uint8_t *data)
{
	TWCR = _BV(TWINT) | _BV(TWEN);
	while (!(TWCR & _BV(TWINT)));
	*data = TWDR;
	return TWSR & TW_STATUS_MASK;
}

void i2c_stop()
{
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

