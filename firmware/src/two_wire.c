#include "two_wire.h"

// TWI_slave_init(uint8_t addr) {
//     TWAR = (addr << 1);
// }

// TWI_master_init(uint8_t addr);

void TWI_start(void) {
    // Send the start condition
    TWCR = (1 << TWINT)  // Clear the TWINT flag
         | (1 << TWSTA)  // set start condition bit
         | (1 << TWEN);  //enable the TWI
    while( !(TWCR & (1 << TWINT)) ) // wait until the start condition is transmitted
        ;
    while((TWSR & 0xF8) != 0x08) // check for ACK
        ;
}

void TWI_master_init(void) {
    TWSR |= (1 << TWPS0) | (1 << TWPS1); // set the TWI prescaler to 64
    TWBR = 0x00;
    // TWBR = (uint8_t)(((F_CPU / F_SCL) - 16) / 2);
}

void TWI_addr_slave(uint8_t addr, bool write) {
    TWDR = (addr << 1) + write; // load address and write bit to TW data register
    TWCR &= ~(1 << TWSTA);
    TWCR = (1 << TWINT) | (1 << TWEN); // send the loaded data to the bus
    while((TWSR & 0xF8) != 0x40) // check for ACK
        ;  
}

void TWI_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while( !(TWCR & (1 << TWSTO)) )
        ;
}