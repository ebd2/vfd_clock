#ifndef BCD_H
#define BCD_H

#include <stdint.h>

uint8_t to_bcd(uint8_t bin, uint8_t mask);

uint8_t from_bcd(uint8_t bcd, uint8_t mask);

#endif
