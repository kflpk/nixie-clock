#include "uart.h"
#include <util/delay.h>


void UART_init(uint32_t baudrate) {
    uint16_t ubrr = (F_CPU / (16 * baudrate)) - 1;
    UBRR0H = (uint8_t) (ubrr >> 8) & 0xFF;
    UBRR0L = (uint8_t) ubrr & 0xFF;

    UCSR0B |= (1 << RXEN0) | (1 < TXEN0) | (1 << TXCIE0) | (1 << RXCIE0);
    UCSR0C = (3 << UCSZ00); // set 8 bits of data
}

void UART_putchar(char c) {
    while( !(UCSR0A & (1 << UDRE0)) )
        ;
    
    UDR0 = c;
}

void UART_println(char* line) {

}