#ifndef DS1307_H
#define DS1307_H

#include <stdbool.h>
#include <inttypes.h>

#include <util/twi.h>
#include <avr/io.h>
#include "two_wire.h"

#define DS_ADDR 0b1101000

#define DS_SEC_REG     0x00
#define DS_MIN_REG     0x01
#define DS_HOUR_REG    0x02

#define DS_WEEKDAY_REG 0x03

#define DS_DAY_REG     0x04
#define DS_MON_REG     0x05
#define DS_YEAR_REG    0x06

#define DS_CTRL_REG    0x07

#define DS_RAMSTART    0x08
#define DS_RAMEND      0xFF

#define bcd2int(bcd) ( 10*((bcd >> 4) & 0b0111) + (bcd & 0b1111))
#define int2bcd(num) (int)( ((num / 10) & 0b1111 << 4) + num % 10 )

struct DS_time {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t day;
    uint8_t month;
    uint8_t year;
};

struct DS_time create_time_struct(uint8_t day, uint8_t month, uint8_t year, 
                                  uint8_t hour, uint8_t minute, uint8_t second);
bool DS_set_time(struct DS_time* time);
bool DS_get_time(struct DS_time* time);

#endif