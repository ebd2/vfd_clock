#include "bcd.h"

uint8_t to_bcd(uint8_t bin, uint8_t mask) {
	uint8_t result = 0;
	uint8_t t;

	t = bin % 10;
	result |= t;

	bin /= 10;
	t = (bin % 10) << 4;

	result |= t;

	return result & mask;
}

uint8_t from_bcd(uint8_t bcd, uint8_t mask) {
	uint8_t result = 0;
	uint8_t t;

	bcd &= mask;

	t = bcd & 0xf;
	result += t;

	bcd >>= 4;
	t = bcd & 0xf;
	result += 10 * t;
	
	return result;
}

