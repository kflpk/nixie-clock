#include "nixie.h"

// TODO: Add cathode poisoning prevention

void display_init() {
    DDRC = 0b111;
}

void display_numbers(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4) {
    push_number(num4);
    push_number(num3);
    push_number(num2);
    push_number(num1);
}

// NOTE: In K155ID1 input A is the least significant bit

void push_number(uint8_t number) {
    number %= 10;

    SER_PORT   &= ~(1 << SER_PIN);
    SRCLK_PORT &= ~(1 << SRCLK_PIN);

    for(int i = 0; i < 4; i++) {
        if( (number >> i) & 1)
            SER_PORT   |=  (1 << SER_PIN);

        _delay_ms(1);
        SRCLK_PORT |=  (1 << SRCLK_PIN);
        _delay_ms(1);
        SRCLK_PORT &= ~(1 << SRCLK_PIN);
        _delay_ms(1);
        SER_PORT   &= ~(1 << SER_PIN);
    }
}

void refresh_display() {
    RCLK_PORT |=  (1 << RCLK_PIN);
    _delay_ms(1);
    RCLK_PORT &= ~(1 << RCLK_PIN);
}
