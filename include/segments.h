#ifndef SEGMENTS_H
#define SEGMENTS_H

typedef enum {
	SS_TOP = 0,
	SS_RT = 1,
	SS_RB = 2,
	SS_BOTTOM = 3,
	SS_LB = 4,
	SS_LT = 5,
	SS_MID = 6,
	SS_VERT = 7,
	SS_DOT = 8,
} segment_shift;

typedef enum {
	S_TOP = 1 << SS_TOP,
	S_RT = 1 << SS_RT,
	S_RB = 1 << SS_RB,
	S_BOTTOM = 1 << SS_BOTTOM,
	S_LB = 1 << SS_LB,
	S_LT = 1 << SS_LT,
	S_MID = 1 << SS_MID,
	S_VERT = 1 << SS_VERT,
	S_DOT = 1 << SS_DOT,
} segments;

# define NUM_SEGMENTS 9

#endif
