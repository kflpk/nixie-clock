#ifndef DS1307_H
#define DS1307_H

#include <util/twi.h>
#include <avr/io.h>
#include <stdbool.h>

#define DS_ADDR 0b1101000

struct DS_time {
    int hour;
    int minute;
    int second;
    int day;
    int month;
    int year;
};

struct DS_time create_time_struct(int day, int month, int year, int hour, int minute, int second) {
    return DS_time {
        .day = day,
        .month = month,
        .year = year,
        .hour = hour,
        .minute = minute,
        .second = second
    };
}
bool DS_set_time(struct DS_time* time);
bool DS_get_time(struct DS_time* time);

#endif