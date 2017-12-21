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
volatile int ok, fail, sFail,lastBuffer, bufferVal, returnCode;;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
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

void USART_getc(USART_TypeDef* USARTx)
{
//	
//	
//	if(buffer[head] != 0)
//	{
//	//print character
//	USART_putc(USARTx, buffer[head]);
//	
//	//clear character from head position
//	buffer[head] = 0;
//	
//	//increase head position
//	if(head == 99) 
//		head = 0;
//	else 
//		head++;
//	}	
//	
//	//busy waiting getc
////  char c;

////  // Was there an Overrun error?
////  if((USARTx->ISR & USART_ISR_ORE) != 0)
////  {
////    // Yes, clear it 
////    USARTx->ICR |= USART_ICR_ORECF;
////  }

////  // Wait for data in the Receive Data Register
////  while((USARTx->ISR & USART_ISR_RXNE) == 0) ;

////  // Read data from RDR, clears the RXNE flag
////  c = (char)USARTx->RDR;

////  return(c);
}

char* USART_getstr(USART_TypeDef* USARTx, char* str)
{
	//constant veranderende data uit buffer vanaf interrupt
	//misschien while loop tot eerste char van Parameter str langs komt
	//zodra die voorbij is een while loop tot laatste char van str, in tussen tijd alles opslaan in buf
	uint8_t strLen = 0;
	char* buf;
	
	strLen = strlen(str);
	while(*buffer != *str){}	//waiting for first bit of str
	str += strLen;						//End of str
	while(*buffer != *str){
		*buf = *str;
		buf++;
	}
	
//		USART_getc(USARTx);
//		//if(c == '\r')break;
//  		USART_putc(USARTx, c);
//	  *str = c;
//		str++;

	
	*buf = '\0';
	
	return buf;
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
