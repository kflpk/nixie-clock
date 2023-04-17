#include "ds1307.h"

uint8_t time_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t rtc_ram[56];

struct DS_time create_time_struct(uint8_t day, uint8_t month, uint8_t year, uint8_t hour, uint8_t minute, uint8_t second) {
    return (struct DS_time) {
        .day = day,
        .month = month,
        .year = year,
        .hour = hour,
        .minute = minute,
        .second = second
    };
}

bool DS_get_time(struct DS_time* time) { // FIXME: add setting to DS_time
    TWI_start();
    TWI_addr_slave(DS_ADDR, TW_WRITE);
    TWI_write_byte(0x00); // set the DS1307 register pointer to the beginning

    TWI_repeated_start();

    TWI_addr_slave(DS_ADDR, TW_READ); // repeated start with read flag
    TWI_read_buffer(time_buffer, 8);
    TWI_stop();
}


bool DS_set_time(struct DS_time* time) { // FIXME: add setting from DS_time
    TWI_start();

    TWI_addr_slave(DS_ADDR, TW_WRITE);
    TWI_write_byte(0x00); // set the DS1307 register pointer to the beginning

    TWI_repeated_start();

    TWI_addr_slave(DS_ADDR, TW_WRITE);
    TWI_write_buffer(time_buffer, 8);

    TWI_stop();
}