#include <avr/io.h>

#include "display.h"

#define PORTB_ADDR ((void *) 0x05)

tube_t tube0 = {
	NULL,
	NULL,
	{
		15, 3, 1, 19, 18, 17, 16, 0, 2
	},
};

hv5812_controller_t controller0 = {
	PORTB_ADDR,
	PORTB0,
	PORTB1,
	PORTB2,
};

grid_t grid0 = {
	PORTB_ADDR,
	PORTB3,
	&controller0,
	0,

	{ &tube0, NULL },
};

tube_t *tubes[] = { &tube0, NULL };
grid_t *grids[] = { &grid0, NULL };

display_t clock_display = {
	sizeof(tubes) / sizeof(tubes[0]),
	tubes,
	sizeof(grids) / sizeof(grids[0]),
	grids,
};

void clock_init()
{
	tube0.controller = &controller0;
	tube0.grid = &grid0;
}
