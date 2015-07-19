#include <string.h>
#include <util/delay.h>

#include "display.h"
#include "tubechars.h"
#include "avrio.h"

#define SET_PIN(port_state, pin) (port_state) |= (1<<(pin))
#define CLEAR_PIN(port_state, pin) (port_state) &= (~(1<<(pin)))

void test_tube(tube_t *tube)
{
	hv5812_controller_t *controller;
	grid_t *grid;

	controller = tube->controller;
	grid = tube->grid;
	
	uint8_t g_port_state = read_port(grid->port);

	SET_PIN(g_port_state, grid->pin);
	write_port(grid->port, g_port_state);

	uint8_t i;
	uint32_t c_data;

	for (i = 0; i < sizeof(tube->seg_map) / sizeof(*tube->seg_map); ++i) {
		c_data = 1L << tube->seg_map[i];
		send_controller(controller, c_data);
		strobe_controller(controller);
		_delay_ms(1000.0);
	}

	CLEAR_PIN(g_port_state, grid->pin);
	write_port(grid->port, g_port_state);
}

void send_controller(hv5812_controller_t *controller, uint32_t data)
{
	int8_t i;
	uint8_t c_port_state = read_port(controller->port);

	CLEAR_PIN(c_port_state, controller->strobe);

	for (i = HV5812_BITS - 1; i >= 0; --i) {
		CLEAR_PIN(c_port_state, controller->clock);
		// set data pin in port state
		if (data & 1L<<i) {
			SET_PIN(c_port_state, controller->data_in);
		} else {
			CLEAR_PIN(c_port_state, controller->data_in);
		}

		write_port(controller->port, c_port_state);
		SET_PIN(c_port_state, controller->clock);
		write_port(controller->port, c_port_state);
	}

	CLEAR_PIN(c_port_state, controller->clock);
	CLEAR_PIN(c_port_state, controller->data_in);
}

void strobe_controller(hv5812_controller_t *c)
{
	uint8_t c_port_state = read_port(c->port);
	SET_PIN(c_port_state, c->strobe);
	write_port(c->port, c_port_state);
	CLEAR_PIN(c_port_state, c->strobe);
	write_port(c->port, c_port_state);
}

void render_tubechar(uint32_t *c_data, tube_t *tube, tubechar_t c)
{
	uint8_t s;

	for (s = 0; s < NUM_SEGMENTS; ++s) {
		if (c & 1L << s) {
			*c_data |= 1L << tube->seg_map[s];
		}
	}
}

void refresh_grid(grid_t *prev_grid, grid_t *grid) {
	send_controller(grid->controller, grid->c_data);
	grid_off(prev_grid);
	strobe_controller(grid->controller);
	grid_on(grid);
}

void grid_on(grid_t *grid)
{
	uint8_t g_port_state;

	g_port_state = read_port(grid->port);
	SET_PIN(g_port_state, grid->pin);
	write_port(grid->port, g_port_state);
}

void grid_off(grid_t *grid)
{
	uint8_t g_port_state;

	g_port_state = read_port(grid->port);
	CLEAR_PIN(g_port_state, grid->pin);
	write_port(grid->port, g_port_state);
}

void say(display_t *disp, char *what)
{
	size_t len = strlen(what);
	size_t i;
	uint8_t t;
	uint8_t g;
	tubechar_t tc;
	uint32_t c_data;
	tube_t *tube;

	for (i = 0; i <= len; ++i) {
		c_data = 0;
		for (g = 0; g < disp->grid_len; ++g) {
			disp->grid[g]->c_data = 0;
		}

		for (t = 0; t < disp->tube_len; ++t) {
			if (i + t < len) {
				if ((tc = to_tubechar(what[i + t])) == -1) {
					tc = NO_CHAR;
				}
			} else {
				tc = BLANK;
			}

			tube = disp->tube[t];
			render_tubechar(&c_data, tube, tc);
			tube->grid->c_data |= c_data;
		}
		_delay_ms(500.0);
	}
}
