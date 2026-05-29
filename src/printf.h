#ifndef __PRINTF_H
#define __PRINTF_H

#include "stm32f4xx.h"
#include <stdio.h>

/**
 * @brief  Initializes the selected USART peripheral with default pins and baud rate.
 *         Automatically enables GPIO & USART peripheral clocks.
 * 
 * @note   Default Pin Configurations:
 *         - USART1: TX = PA9,  RX = PA10  (AF7)
 *         - USART2: TX = PA2,  RX = PA3   (AF7)
 *         - USART3: TX = PB10, RX = PB11  (AF7)
 *         - UART4:  TX = PC10, RX = PC11  (AF8)
 *         - UART5:  TX = PC12, RX = PD2   (AF8)
 *         - USART6: TX = PC6,  RX = PC7   (AF8)
 * 
 * @param  USARTx: Select USART/UART peripheral (USART1, USART2, USART3, UART4, UART5, USART6)
 * @param  baudrate: The desired communication baud rate (e.g. 9600, 115200)
 * @retval None
 */
void USART_Printf_Init(USART_TypeDef* USARTx, uint32_t baudrate);

/**
 * @brief  Sends a single character via USART. Blocks until transmitter is ready.
 * @param  ch: Character to send
 * @retval None
 */
void USART_SendChar(char ch);

/**
 * @brief  Sends a null-terminated string via USART.
 * @param  str: Pointer to the string
 * @retval None
 */
void USART_SendString(const char* str);

/**
 * @brief  Receives a single character via USART. Blocks until a character is received.
 * @retval The received character
 */
char USART_ReceiveChar(void);

/**
 * @brief  Checks if new serial data is available to read (non-blocking).
 * @retval 1 if data is available, 0 otherwise
 */
uint8_t USART_HasData(void);

#endif /* __PRINTF_H */
