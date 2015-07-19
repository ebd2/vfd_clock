#ifndef I2C_H
#define I2C_H

#include <stdint.h>

uint8_t i2c_start();
uint8_t i2c_sla(uint8_t addr, uint8_t rw);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(uint8_t *data);
uint8_t i2c_read_nack(uint8_t *data);
void i2c_stop();

#endif
