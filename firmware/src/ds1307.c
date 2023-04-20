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

void parse_time_buffer(struct DS_time* time) {
    time_buffer[0] = int2bcd(time->second) & 0b01111111;
    time_buffer[1] = int2bcd(time->minute) & 0b00111111; // bit 6 cleared for 24 hour mode
    time_buffer[2] = int2bcd(time->hour);
    // byte 3 is for weekday which is supported for this clock
    time_buffer[4] = int2bcd(time->day);
    time_buffer[5] = int2bcd(time->month);
    time_buffer[6] = int2bcd(time->year);
}

bool DS_get_time(struct DS_time* time) {
    parse_time_buffer(time);

    TWI_start();

    TWI_addr_slave(DS_ADDR, TW_WRITE);
    TWI_write_byte(0x00); // set the DS1307 register pointer to the beginning

    TWI_repeated_start();
    TWI_addr_slave(DS_ADDR, TW_READ); // repeated start with read flag

    TWI_read_buffer(time_buffer, 8);

    TWI_stop();
}


bool DS_set_time(struct DS_time* time) {
    parse_time_buffer(time);

    TWI_start();

    TWI_addr_slave(DS_ADDR, TW_WRITE);
    TWI_write_byte(0x00); // set the DS1307 register pointer to the beginning

    TWI_repeated_start();
    TWI_addr_slave(DS_ADDR, TW_WRITE);

    TWI_write_buffer(time_buffer, 8);

    TWI_stop();
}