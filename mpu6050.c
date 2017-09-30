#include "mpu6050.h"

#define MPU6050_GYRO_FS MPU6050_GYRO_FS_2000
#define MPU6050_ACCEL_FS MPU6050_ACCEL_FS_2

#include <util/delay.h>

#include "i2c.h"

static uint8_t MPU6050_address = MPU6050_DEFAULT_ADDRESS << 1;

int8_t MPU6050_init(uint8_t address)
{
    MPU6050_address = (address << 1);
    if(MPU6050_setSleep(0) < 0)
        return -1;

    MPU6050_writeBits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_XGYRO);
    MPU6050_writeBits(MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, MPU6050_DLPF_BW_42);
    MPU6050_writeByte(MPU6050_RA_SMPLRT_DIV, 4);
    MPU6050_writeBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS);
    MPU6050_writeBits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, MPU6050_ACCEL_FS);

    return 0;
}

int8_t MPU6050_setSleep(uint8_t sleep)
{
    sleep = sleep > 0 ? 1 : 0;
    if(MPU6050_writeBit(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, sleep) < 0)
        return -1;

    return 0;
}

int8_t MPU6050_writeBytes(uint8_t address, uint8_t *data, uint16_t length)
{
    uint16_t i;

    if(I2C_start(MPU6050_address | I2C_WRITE) < 0)
        return -1;
    if(I2C_write(address) < 0)
        return -2;
    for(i = 0; i < length; i++)
        I2C_write(*(data + i));
    I2C_stop();

    return 0;
}

int8_t MPU6050_readBytes(uint8_t address, uint8_t *data, uint16_t length)
{
    uint16_t i;

    if(I2C_start(MPU6050_address | I2C_WRITE) < 0)
        return -1;
    if(I2C_write(address) < 0)
        return -2;
    I2C_stop();
    _delay_ms(10);
    I2C_start(MPU6050_address | I2C_READ);
    for(i = 0; i < length - 1; i++)
        *(data + i) = I2C_readAck();
    *(data + i) = I2C_readNAck();
    I2C_stop();

    return 0;
}

int8_t MPU6050_writeByte(uint8_t address, uint8_t data)
{
    MPU6050_readBytes(address, &data, 1);
}

int8_t MPU6050_readByte(uint8_t address, uint8_t *data)
{
    MPU6050_readBytes(address, data, 1);
}

int8_t MPU6050_writeBit(uint8_t address, uint8_t bit, uint8_t data)
{
    uint8_t byte;
    if(MPU6050_readBytes(MPU6050_address, &byte, 1) < 0)
        return -1;
    byte = data > 0 ? byte | (1 << bit) : byte & ~(1 << bit);
    _delay_ms(10);
    if(MPU6050_writeBytes(MPU6050_address, &byte, 1) < 0)
        return -2;

    return 0;
}

int8_t MPU6050_readBit(uint8_t address, uint8_t bit)
{
    uint8_t byte;
    if(MPU6050_readBytes(MPU6050_address, &byte, 1) < 0)
        return -1;

    return (byte >> bit) & 0x01;
}

int8_t MPU6050_writeBits(uint8_t address, uint8_t startBit, uint8_t length, uint8_t data)
{
    if(length <= 0)
        return 0;

    uint8_t byte;
    if(MPU6050_readBytes(address, &byte, 1) < 0)
        return -1;

    uint8_t mask = (1 << length) - 1;
    mask <<= (startBit - length + 1);
    data <<= (startBit - length + 1);
    data &= mask;
    byte &= ~(mask);
    byte |= data;

    _delay_ms(10);
    if(MPU6050_writeBytes(address, &byte, 1) < 0)
        return -2;

    return 0;
}

int8_t MPU6050_readBits(uint8_t address, uint8_t startBit, uint8_t length, uint8_t *data)
{
    if(length <= 0)
        return 0;

    uint8_t byte;
    if(MPU6050_readBytes(address, &byte, 1) < 0)
        return -1;

    uint8_t mask = (1 << length) - 1;
    byte >>= (startBit - length + 1);
    byte &= mask;
    *(data) = byte;

    return 0;
}
