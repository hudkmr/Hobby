/*
 * uart_driver.c
 *
 *  Created on: Mar 19, 2016
 *      Author: KEERTHANA
 */

#include "uart_driver.h"

unsigned char deneme[]="armprogramming.com";
unsigned char ReceivedBytescount;
unsigned char Veri[255];

/***************************************************************************************
Fonksiyon:USART_Configuration
Amaç     :Configuration for UART
Kullanım :USART_Configuration(BaudRate);
***************************************************************************************/
void USART_Configuration(unsigned int BaudRate)
{
  //
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* USART init */
  USART_Init(USART1, &USART_InitStructure);
  /* USART1 enable */
  USART_Cmd(USART1, ENABLE);
  /*USART1 RX interrupt enable*/
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

/***************************************************************************************
Interrupt Su Routine
Amaç     :Get Interrupt Datas to Veri[]
***************************************************************************************/
void USART1_IRQHandler(void)
{

  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Received characters modify string
  {
    Veri[ReceivedBytescount] = USART_ReceiveData(USART1);
    ReceivedBytescount++;
    if (ReceivedBytescount >= 255)
    	ReceivedBytescount=0;
  }
}
/***************************************************************************************
Fonksiyon:USART_Write
Amaç     :Send Data from UART
Kullanım :USART_Write("armprogramming.com");
***************************************************************************************/
void USART_Write(char *string){

    while(*string){
        // wait until data register is empty
        while( !(USART1->SR & 0x00000040) );
        	USART_SendData(USART1,*string++);
    }
}

