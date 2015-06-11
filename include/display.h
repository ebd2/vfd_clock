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

	/* HV5812 controller can drive two tubes */
	tube_t *tube[2];
} hv5812_controller_t;

typedef struct grid {
	/* port and pin information for driving the grid */
	void *port;
	uint8_t pin;

	// struct hv5812_controller *controller;
	hv5812_controller_t *controller;
	uint32_t c_data;

	tube_t *tube[2];
} grid_t;

typedef struct display {
	uint8_t tube_len;
	tube_t **tube;
	uint8_t grid_len;
	grid_t **grid;
} display_t;

void test_tube(tube_t *tube);

void display(display_t *display, char *s, off_t index);

void send_controller(hv5812_controller_t *controller, uint32_t data);

void render_tubechar(uint32_t *c_data, tube_t *tube, tubechar_t c);

void refresh(display_t *display);

#endif
