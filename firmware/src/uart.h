#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <inttypes.h>
#include <avr/io.h>

void UART_init(uint32_t baudrate);
void UART_putchar(char c);
void UART_println(char* line);

#endif