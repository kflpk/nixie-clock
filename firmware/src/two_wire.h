#ifndef TWO_WIRE_H
#define TWO_WIRE_H

#include <inttypes.h>
#include <stdbool.h>

#include <util/twi.h>

void TWI_master_init(void);

void TWI_start(void);
void TWI_repeated_start(void);
void TWI_stop(void);

void TWI_read_data(void); // TODO
void TWI_write_data(void); // TODO
void TWI_addr_slave(uint8_t addr, bool write);

#endif