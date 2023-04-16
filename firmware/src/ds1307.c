#include "ds1307.h"


struct DS_time create_time_struct(int day, int month, int year, int hour, int minute, int second) {
    return (struct DS_time) {
        .day = day,
        .month = month,
        .year = year,
        .hour = hour,
        .minute = minute,
        .second = second
    };
}