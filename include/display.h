#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

#include "segments.h"
#include "tubechars.h"

#define CLOCK_TUBES 4

#define HV5812_BITS 20

struct hv5812_controller;
struct mux;

typedef struct tube {
	struct grid *grid;
	struct hv5812_controller *controller;
	uint8_t seg_map[NUM_SEGMENTS];
} tube_t;

typedef struct hv5812_controller {
	/* port and pin information for driving the controller */
	void *port;
	uint8_t data_in;
	uint8_t clock;
	uint8_t strobe;
} hv5812_controller_t;

typedef struct grid {
	/* port and pin information for driving the grid */
	void *port;
	uint8_t pin;

	hv5812_controller_t *controller;
	uint32_t c_data;

	tube_t *tube[2];
} grid_t;

typedef struct display {
	// The tubes in visual order (i.e. left-to-right)
	uint8_t tube_len;
	tube_t **tube;
	// The grid circuits.  Any order should be OK.
	uint8_t grid_len;
	grid_t **grid;
	// the index of the currently active grid
	uint8_t active_grid;
} display_t;

void test_tube(tube_t *tube);

void display(display_t *display, char *s, off_t index);

void send_controller(hv5812_controller_t *controller, uint32_t data);
void strobe_controller(hv5812_controller_t *c);

void render_tubechar(uint32_t *c_data, tube_t *tube, tubechar_t c);

void refresh_grid(grid_t *prev_grid, grid_t *grid);

void grid_on(grid_t *grid);
void grid_off(grid_t *grid);

#endif
