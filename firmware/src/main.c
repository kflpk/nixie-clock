// #define __AVR_ATmega328P__

#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include "two_wire.h"
#include "ds1307.h"
#include "nixie.h"


uint8_t buf[64] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int main() {
    return 0;
}
