#ifndef _I2C_H_
#define _I2C_H_

#define I2C_WRITE       0x00
#define I2C_READ        0x01

#include <stdint.h>

/**
 * @brief
 *  Initialize TWI
 *
 * @param frequency - Frequency of I2C
 */
void I2C_init(uint32_t frequency);

/**
 * @brief
 *  Start communication to slave device
 *
 * Send start signal
 *
 * @param address - Address of slave device (included write or read bit)
 * @return 0 if no error or negative number if error occure
 */
int8_t I2C_start(uint8_t address);

/**
 * @brief
 *  End communication
 *
 * Send stop signal
 */
void I2C_stop(void);

/**
 * @brief
 *  Write data
 *
 * Write data to bus
 *
 * @param data - Data to be writen on bus
 */
int8_t I2C_write(uint8_t data);

/**
 * @brief
 *  Read acknowledged
 *
 * @return Readed data (acknowledged)
 */
uint8_t I2C_readAck(void);

/**
 * @brief
 *  Read data without acknowledged
 *
 * @return Readed data
 */
uint8_t I2C_readNAck(void);

#endif // _I2C_H_
