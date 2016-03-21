/*
 * uart_driver.h
 *
 *  Created on: Mar 19, 2016
 *      Author: KEERTHANA
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "bootloader_main.h"

void USART_Configuration(unsigned int BaudRate);
void USART1_IRQHandler(void);
void USART_Write(char *string);


#endif /* UART_DRIVER_H_ */
