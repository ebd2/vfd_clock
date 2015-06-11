#ifndef TUBECHARS_H
#define TUBECHARS_H

#include <stdint.h>

typedef int16_t tubechar_t;

extern tubechar_t BLANK;
extern tubechar_t NO_CHAR;

#define DIGITS_LEN 10
extern tubechar_t DIGITS[DIGITS_LEN];

#define LETTERS_LEN 26
extern tubechar_t LETTERS[LETTERS_LEN];

tubechar_t to_tubechar(char c);

#endif
