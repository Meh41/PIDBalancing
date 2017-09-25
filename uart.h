#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>

/**
 * @brief
 *  Init UART communication
 *
 * @param baud - Baud rate of communication
 */
void UART_init(int32_t baud);

/**
 * @brief
 *  Send character
 *
 * @param ch - Character to be sent
 */
void UART_putchar(char ch);

/**
 * @brief
 *  Send string
 *
 * @param str - String to be sent
 */
void UART_putstr(const char *str);

/**
 * @brief
 *  Send unsigned 64bit integer
 *
 * @param number - Integer to be sent
 */
void UART_putuint(uint64_t number);

/**
 * @brief
 *  Send signed 64bit integer
 *
 * @param number - Integer to be sent
 */
void UART_putint(int64_t number);

#endif // _UART_H_
