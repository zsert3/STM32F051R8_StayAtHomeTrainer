/**
  ******************************************************************************
  * @file    sendReceiveUART.c 
  * @author  
  * @version V0.0.0
  * @date    
  * @brief   
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sendReceiveUART.h"
#include "stm32f0xx.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Global variables ----------------------------------------------------------*/
volatile char* buffer;
volatile int ok, fail, sFail, returnCode, isSet, timeOutIT;
volatile char lastBuffer, bufferVal;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TIMEOUT 200000
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
	void USART_BaudrateDetect(void);
/* Private functions ---------------------------------------------------------*/

void USART_init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
  //Configure USART2 pins: Rx (PA2) and Tx (PA3)
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //Configure USART2 setting: ----------------------------
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(USART2, &USART_InitStructure);
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART2,ENABLE);
  USART_Cmd(USART1,ENABLE);
	
	/* Enable RXNE interrupt */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	/* Enable USART1 global interrupt */
	NVIC_EnableIRQ(USART2_IRQn);
	
}

void USART_putEnter(void){
	USART_putc(USART2, '\r');
	USART_putc(USART2, '\n');
}

void USART_putc(USART_TypeDef* USARTx, char c)
{
  // Wait for Transmit data register empty
  while((USARTx->ISR & USART_ISR_TXE) == 0) ;

  // Transmit data by writing to TDR, clears TXE flag  
  USARTx->TDR = c;
}

void USART_putstr(USART_TypeDef* USARTx, char *str)
{
  while(*str)
  {
    USART_putc(USARTx, *str++);
  }
}


/**
  * @brief  This function waits untill str1 is received through USART2
						for instance 'OK' when a message is send correctly
	* @param 	str: this is the string the function will search for
	* @retval 0: Error state
						1: String found]
  */
uint8_t USART_getstr(char* str)
{
	uint8_t i;
	uint8_t strLen = 0;
	uint8_t timeOut = 8;
	
	timeOutIT = 0;
	strLen = strlen(str);
	
	//Start timeout Timer
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_Cmd(TIM2, ENABLE);
	
	while(timeOut > 0){
		
		while(bufferVal != *str){	//waiting for first bit of str !!TIMER INTERRUPT!!
			if(timeOutIT == 1){
				USART_putstr(USART1, "TIMEOUT\r\n");
				timeOut = 0;
				//TIM_Cmd(TIM2, DISABLE);	//stop timer
				return 0;
			}
		}
		
		//search for next chars
		for(i = 1; i<strLen; i++){
			str++;
			isSet = 0; 
			while(!isSet);	//set from interrupt when a new char comes in
			
			if(bufferVal != *str){
				//USART_putstr(USART1, "ALLES IS KAPOT!!\r\n");
				str -= i;
				timeOut--;
				break;
			}else{
				//USART_putstr(USART1, "Nog een gevonden!!\r\n");
				if(i == strLen-1){
					//USART_putstr(USART1, "HOOOI");
					TIM_Cmd(TIM2, DISABLE);	//stop timer
					return 1;
				}
			}
		}
	}
	if(timeOut == 0){
		return 0;
	}
	
}


// Implements the following VT100 terminal commands
// - Clear screan
// - Cursor home
void USART_clearscreen(USART_TypeDef* USARTx)
{
  char cmd1[5] = {0x1B, '[', '2', 'J', '\0'}; // Clear screen
  char cmd2[4] = {0x1B, '[', 'f', '\0'}; // Cursor home
  
  USART_putstr(USARTx, cmd1);
  USART_putstr(USARTx, cmd2);
}
