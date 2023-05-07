#include "two_wire.h"

void TWI_master_init(void) {
    TWSR |= (1 << TWPS0) | (1 << TWPS1); // set the TWI prescaler to 64
    TWBR = 0x01;
}

void TWI_start(void) {
    int retries = 10;
    // Send the start condition
    TWCR = (1 << TWINT)  // Clear the TWINT flag
         | (1 << TWSTA)  // set start condition bit
         | (1 << TWEN);  //enable the TWI
    while( !(TWCR & (1 << TWINT)) ) // wait until the start condition is transmitted
        ;
    while(TW_STATUS != TW_START) {
            retries--;
            if(retries == 0)
                break;
            _delay_us(50);
    }
}

void TWI_repeated_start(void) {
    int retries = 10;
    // Send the start condition
    TWCR = (1 << TWINT)  // Clear the TWINT flag
         | (1 << TWSTA)  // set start condition bit
         | (1 << TWEN);  //enable the TWI
    while( !(TWCR & (1 << TWINT)) ) // wait until the start condition is transmitted
        ;

    while(TW_STATUS != TW_REP_START) {// check for ACK
            retries--;
            if(retries == 0)
                break;
            _delay_us(50);
    }
}

void TWI_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while( !(TWCR & (1 << TWSTO)) )
        ;
}


void TWI_addr_slave(uint8_t addr, bool write) {
    int retries = 100;
    TWDR = (addr << 1) + write; // load address and write bit to TW data register
    TWCR &= ~(1 << TWSTA);
    TWCR = (1 << TWINT) | (1 << TWEN); // send the loaded data to the bus

    if(write == TW_WRITE) { // for Master Transmitter mode
        while(TW_STATUS != 0x18) { // SLA+W transmitted, ACK received
            retries--;
            if(retries == 0)
                break;
            _delay_us(50);
        }
    } else { // for Master Receiver mode
        while(TW_STATUS != 0x40) { // SLA+R transmitted, ACK received
            retries--;
            if(retries == 0)
                break;
            _delay_us(50);
        }
    }
}

void TWI_write_byte(uint8_t data) {
    int i = 0;
    TWDR = data; // load data to the TW data register
    TWCR = (1 << TWINT) | (1 << TWEN); // send the loaded data to the bus
    while( !(TWCR & (1 << TWINT)) )
        ;
    while(TW_STATUS != TW_MT_DATA_ACK) // Data transmitted, ACK received
        ;
}

uint8_t TWI_read_byte(bool ACK) {
    int retries = 10;
    uint8_t recv_data;

	TWCR = (1 << TWINT) | (1 << TWEN) | (ACK << TWEA);    // Clear TWI interrupt flag,Enable TWI

	while( !(TWCR & (1<<TWINT)) ) {// Wait till complete TWDR byte transmitted
    }

    if(ACK) {
        while(TW_STATUS != TW_MR_DATA_ACK) { // Data received, ACK returned
            retries--;
            if(retries == 0)
                break;
            _delay_us(50);
        }
    } else {
        while(TW_STATUS != TW_MR_DATA_NACK) { // Data received, NACK returned
            retries--;
            if(retries == 0)
                break;
            _delay_us(50);
        }
    }

	recv_data = TWDR;

    return recv_data;
}

void TWI_read_buffer(uint8_t* buffer, int length) {
    for(int i = 0; i < length; i++) {
        bool ACK = true;
        if(i == length - 1)
            ACK = false;

        buffer[i] = TWI_read_byte(ACK);
    }
}

void TWI_write_buffer(uint8_t* buffer, int length) {
    for(int i = 0; i < length; i++) {
        TWI_write_byte(buffer[i]);
    }
}