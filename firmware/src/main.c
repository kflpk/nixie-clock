// #define __AVR_ATmega328P__

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "two_wire.h"
#include "uart.h"
#include "ds1307.h"
#include "nixie.h"
#include "uart_hal.h"

int main() {
    DDRB = (1 << PB5);
    display_init();
    uart_init(9600, false);


    int i = 0;

    sei();

    while(true) {
        PORTB |= (1 << PB5);
        _delay_ms(1000);
        PORTB &= ~(1 << PB5);
        _delay_ms(1000);

        uart_send_string("Starting TWI\n");
        TWI_start();
        uart_send_string("TWI started\n");

        uart_send_string("Sending TWI address\n");
        TWI_addr_slave(DS_ADDR, TW_READ);
        uart_send_string("TWI address sent\n");

        uart_send_string("Stopping TWI\n");
        TWI_stop();
        uart_send_string("TWI stopped\n");

        _delay_ms(1000);

        i = i % 10;
        i++;
        display_numbers(i, i, i, i);
        refresh_display();
    }


    return 0;
}
