#ifndef AVRIO_H
#define AVRIO_H

#include <avr/io.h>

#define read_port(port_addr) _SFR_IO8(port_addr)
#define write_port(port_addr, data) _SFR_IO8(port_addr) = data

#endif
