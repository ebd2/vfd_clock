#ifndef CLOCK_H
#define CLOCK_H

#include "display.h"

/* Individual tubes, controllers and grids */
extern tube_t tube0;

extern hv5812_controller_t controller0;

extern grid_t grid0;
extern grid_t grid1;

/* collections of tubes and grids that make up the clock */
extern tube_t *tubes[];
extern grid_t *grids[];

/* the clock itself */
extern display_t clock_display;

/*
 * Must be called to initialize a few structure members that cannot be
 * initialized at compile time.
 */
void clock_init();

#endif
