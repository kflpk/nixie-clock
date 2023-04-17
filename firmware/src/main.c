// #define __AVR_ATmega328P__

#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include "two_wire.h"
#include "ds1307.h"
#include "nixie.h"

int main() {
    uint8_t buf[64] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    DDRB = (1 << PB5);
    display_init();

    PORTB |= (1 << PB5);
    _delay_ms(1000);
    PORTB &= ~(1 << PB5);
    _delay_ms(1000);

    while(true) {
        DS_get_time(0);
        _delay_ms(10000);
    }

    display_numbers(2, 1, 3, 7);
    refresh_display();

    while(true)
        ;
    return 0;
}
