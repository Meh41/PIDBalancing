#ifndef F_CPU
#define F_CPU 16000000UL
#endif // F_CPU

#include "i2c.h"

#include <util/twi.h>

void I2C_init(uint32_t frequency)
{
    TWBR = (uint8_t)(((F_CPU / frequency) - 16 ) / 2);
}

int8_t I2C_start(uint8_t address)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));

    if((TWSR & 0xF8) != TW_START)
        return -1;

    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));

    uint8_t twsr = TW_STATUS & 0xF8;
    if((twsr != TW_MR_SLA_ACK) && (twsr != TW_MT_SLA_ACK))
        return -2;

    return 0;
}

void I2C_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

int8_t I2C_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));

    if((TWSR & 0xF8) != TW_MT_DATA_ACK)
        return -1;

    return 0;
}

uint8_t I2C_readAck(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while(!(TWCR & (1 << TWINT)));

    return TWDR;
}

uint8_t I2C_readNAck(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));

    return TWDR;
}
