#ifndef NIXIE_H
#define NIXIE_H

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

#define SER_PORT   PORTC
#define SER_PIN    PC0

#define SRCLK_PORT PORTC
#define SRCLK_PIN  PC1

#define RCLK_PORT  PORTC
#define RCLK_PIN   PC2

void display_init();
void display_numbers(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4);
void push_number(uint8_t number);
void refresh_display(void);

#endif