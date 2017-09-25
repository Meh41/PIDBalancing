#ifndef F_CPU
#define F_CPU 16000000UL
#endif // F_CPU

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "i2c.h"
#include "mpu6050.h"

int main(void)
{
    UART_init(9600);
    I2C_init(100000L);
    MPU6050_init(MPU6050_ADDRESS_AD0_LOW);

    UART_putstr("###############\n");
    UART_putstr("# PIDBalancer #\n");
    UART_putstr("###############\n\n");

    _delay_ms(100);
    while(1)
    {
        uint8_t byte;
        if(MPU6050_readBytes(0x3B, &byte, 1) >= 0);
            UART_putuint(byte);

        _delay_ms(100);
    }

    while(1);

    return 0;
}
