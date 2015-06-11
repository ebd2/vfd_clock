#include <stdint.h>
#include <stddef.h>

uint8_t io_regs[0xC];

uint8_t read_port(void *port_addr)
{
	return *(io_regs + (size_t) port_addr);
}

void write_port(void *port_addr, uint8_t data)
{
	*(io_regs + (size_t) port_addr) = data;
}
