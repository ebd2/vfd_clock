#include <ctype.h>

#include "tubechars.h"
#include "segments.h"

#define NO_CHAR_BITS S_RT | S_RB | S_LB | S_LT | S_MID | S_VERT

tubechar_t BLANK = 0;
tubechar_t NO_CHAR = NO_CHAR_BITS;

tubechar_t DIGITS[10] = {
	// 0
	S_TOP | S_RT | S_RB | S_BOTTOM | S_LB | S_LT, // 0
	S_RT | S_RB,
	S_TOP | S_RT | S_MID | S_BOTTOM | S_LB,
	S_TOP | S_RT | S_RB | S_BOTTOM | S_MID,
	S_RT | S_RB | S_LT | S_MID,
	// 5
	S_TOP | S_RB | S_MID | S_BOTTOM | S_LT,
	S_TOP | S_RB | S_BOTTOM | S_LB | S_LT | S_MID,
	S_TOP | S_RT | S_RB,
	S_TOP | S_RT | S_RB | S_BOTTOM | S_LB | S_LT | S_MID,
	S_TOP | S_RT | S_RB | S_BOTTOM | S_LT | S_MID, // 9
};

tubechar_t LETTERS[26] = {
	// A
	S_TOP | S_RT | S_RB | S_LB | S_LT | S_MID,
	S_RB | S_BOTTOM | S_LB | S_LT | S_MID,
	S_TOP | S_BOTTOM | S_LB | S_LT,
	S_RT | S_RB | S_BOTTOM | S_LB | S_MID,
	S_TOP | S_BOTTOM | S_LB | S_LT | S_MID,
	// F
	S_TOP | S_LB | S_LT | S_MID,
	S_TOP | S_RB | S_BOTTOM | S_LB | S_LT,
	S_RT | S_RB | S_LB | S_LT | S_MID,
	S_TOP | S_BOTTOM | S_VERT,
	S_RT | S_RB | S_BOTTOM | S_LB,
	// K
	NO_CHAR_BITS,
	S_BOTTOM | S_LB | S_LT,
	S_TOP | S_RT | S_RB | S_LB | S_LT | S_VERT,
	S_RB | S_LB | S_MID,
	S_RB | S_BOTTOM | S_LB | S_MID,
	// P
	S_TOP | S_RT | S_LB | S_LT | S_MID,
	S_TOP | S_RT | S_RB | S_LT | S_MID,
	S_MID | S_LB,
	S_TOP | S_RB | S_MID | S_BOTTOM | S_LT,
	S_TOP | S_VERT,
	// U
	S_RT | S_RB | S_BOTTOM | S_LB | S_LT,
	NO_CHAR_BITS,
	S_RT | S_RB | S_BOTTOM | S_LB | S_LT | S_VERT,
	NO_CHAR_BITS,
	S_RT | S_RB | S_BOTTOM | S_LT | S_MID, // 9
	// Z
	NO_CHAR_BITS,
};

tubechar_t to_tubechar(char c)
{
	if (isalpha(c)) {
		return LETTERS[tolower(c) - 'a'];
	} else if (isdigit(c)) {
		return DIGITS[c - '0'];
	} else if (isspace(c)) {
		return BLANK;
	}

	return -1;
}
