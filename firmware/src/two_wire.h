#ifndef TWO_WIRE_H
#define TWO_WIRE_H

#include <inttypes.h>
#include <stdbool.h>

#include <util/twi.h>
#include <util/delay.h>

void TWI_master_init(void);

void TWI_start(void);
void TWI_repeated_start(void);
void TWI_stop(void);

void TWI_addr_slave(uint8_t addr, bool write);
uint8_t TWI_read_byte(bool ACK);
void TWI_read_buffer(uint8_t* buffer, int length);
void TWI_write_byte(uint8_t data);
void TWI_write_buffer(uint8_t* buffer, int length);

#endif