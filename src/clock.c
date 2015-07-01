#include <avr/interrupt.h>
#include <avr/io.h>

#include "display.h"

#define PORTB_ADDR ((void *) 0x05)

tube_t tube0 = {
	NULL,
	NULL,
	{
		15, 3, 1, 19, 18, 17, 16, 0, 2,
	},
};

tube_t tube1 = {
	NULL,
	NULL,
	{
		4, 5, 6, 7, 8, 9, 10, 11, 12,
	},
};

tube_t tube2 = {
	NULL,
	NULL,
	{
		15, 3, 1, 19, 18, 17, 16, 0, 2,
	},
};

tube_t tube3 = {
	NULL,
	NULL,
	{
		4, 5, 6, 7, 8, 9, 10, 11, 12,
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

	{ &tube0, &tube1 },
};

grid_t grid1 = {
	PORTB_ADDR,
	PORTB4,
	&controller0,
	0,

	{ &tube2, &tube3 },
};

tube_t *tubes[] = { &tube0, &tube1, &tube2, &tube3 };
grid_t *grids[] = { &grid0, &grid1 };

display_t display0 = {
	sizeof(tubes) / sizeof(tubes[0]),
	tubes,
	sizeof(grids) / sizeof(grids[0]),
	grids,
};

void clock_init()
{
	// Fill in addresses not known at compile time.
	tube0.controller = &controller0;
	tube0.grid = &grid0;
	tube1.controller = &controller0;
	tube1.grid = &grid0;

	tube2.controller = &controller0;
	tube2.grid = &grid1;
	tube3.controller = &controller0;
	tube3.grid = &grid1;

	// Set up PWM for timer0
	// DDRD |= (1 << DDD5);
	// DDRD |= (1 << DDD6);

	// Set for fast PWM mode
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	// set prescaler to 64 and enable timer0
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Enable the overflow interrupt
	TIMSK0 |= (1 << TOIE0);
}

ISR(TIMER0_OVF_vect) {
	TIFR0 |= (1 << TOV0);

	uint8_t next_grid = (display0.active_grid + 1) % display0.grid_len;

	refresh_grid(display0.grid[display0.active_grid],
			display0.grid[next_grid]);

	display0.active_grid = next_grid;
}
