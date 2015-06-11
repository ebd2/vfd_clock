#ifndef AVRIO_H
#define AVRIO_H

uint8_t read_port(void *port_addr);
void write_port(void *port_addr, uint8_t data);

#endif
