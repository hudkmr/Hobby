/*
 * sys_config.c
 *
 *  Created on: Mar 19, 2016
 *      Author: KEERTHANA
 */

#include "sys_config.h"

/**************************************************************************************
Function:RCC_Configuration
Description     :Clock Configuration
***************************************************************************************/
void RCC_Configuration(void)
{
/* GPIO CLOCK  */
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
/* UART CLOCK  */
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

/**************************************************************************************
Function:GPIO_Configuration
Description     :GPIO Configuration for UART Pins
**************************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* USART TX  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  // PA.09 USART1.TX-
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* USART RX Pin Ayarı */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // PA.10 USART1.RX-
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/***************************************************************************************
Function:NVIC_Configuration
Description     :Interrupt Configuration
***************************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

