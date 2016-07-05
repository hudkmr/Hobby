//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Interrupt_Init(void);

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
  GPIO_InitTypeDef GPIO_InitStruct;

  //Initialize the System
  SystemInit();

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

  //SET GPIOC To Ouptut Port
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  //SET GPIOD To Input Port
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    Interrupt_Init();
    EXTI_GenerateSWInterrupt(EXTI_Line3);
  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}


void Interrupt_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;

	//Configuring EXTI Line 3
	EXTI_InitStruct.EXTI_Line = EXTI_Line3;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	//Enable and set EXTI Line 2 interrupt to Lowest Priority
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

}

void EXTI3_IRQHandler(void)
{
	//Delay_ms(1000);//debounce. FOR TEST. but I changed for 1,2,10.
   if(EXTI_GetITStatus(EXTI_Line3) != RESET)
   {
     /* SET LED */
     GPIO_SetBits(GPIOC, GPIO_Pin_4);
   }

   if(EXTI_GetITStatus(EXTI_Line3) == RESET)
   {
	/* RESET LED */
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
   }
/* Clear the EXTI line 0 pending bit */
EXTI_ClearITPendingBit(EXTI_Line3);
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
