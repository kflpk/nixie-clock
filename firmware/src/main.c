// #define __AVR_ATmega328P__

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

#include "two_wire.h"
#include "ds1307.h"
#include "nixie.h"

int main() {
    DDRB = (1 << PB5);
    display_init();


    int i = 0;
    while(true) {
        PORTB |= (1 << PB5);
        _delay_ms(1000);
        PORTB &= ~(1 << PB5);
        _delay_ms(1000);

        TWI_start();
        TWI_addr_slave(DS_ADDR, TW_READ);
        TWI_stop();
        _delay_ms(1000);

        i = i % 10;
        i++;
        display_numbers(i, i, i, i);
        refresh_display();
    }
    return 0;
}
