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
#include "stm32f0xx_gpio.h"
#include <stdio.h>
#include <stdint.h>

/* Global variables ----------------------------------------------------------*/
volatile char rx_buffer;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
	void USART_BaudrateDetect(void);
/* Private functions ---------------------------------------------------------*/

void USART_init(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	USART_InitTypeDef				USART_InitStructure;
	
  // GPIOA Periph clock enable
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
  // PA9 and PA10 Alternate function mode
  GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);
  
  // Set alternate functions AF1 for PA9 and PA10
  GPIOA->AFR[1] |= 0x00000110;
  
  // USART1 clock enable
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 

  // 115200 Bd @ 48 MHz
  // USARTDIV = 48 MHz / 115200 = 416 = 0x01A0
  // BRR[15:4] = USARTDIV[15:4]
  // When OVER8 = 0, BRR [3:0] = USARTDIV [3:0]
  USART1->BRR = 0x01A0;

  // USART enable
  // Receiver enable
  // Transmitter enable
  USART1->CR1 = USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;

  // Default value
  USART1->CR2 = 0;
  USART1->CR3 = 0; 
  
//   // RXNE interrupt enable
//   USART1->CR1 |= USART_CR1_RXNEIE;
//   
//   // USART1 interrupts enable in NVIC
//   NVIC_EnableIRQ(USART1_IRQn);
//   NVIC_SetPriority(USART1_IRQn, 0);
//   NVIC_ClearPendingIRQ(USART1_IRQn);

}

void USART_putc(char c)
{
  // Wait for Transmit data register empty
  while((USART1->ISR & USART_ISR_TXE) == 0) ;

  // Transmit data by writing to TDR, clears TXE flag  
  USART1->TDR = c;
}

void USART_putstr(char *str)
{
  while(*str)
  {
    if(*str == '\n')
    {
      USART_putc('\r');
    }
    
    USART_putc(*str++);
  }
}

char USART_getc(void)
{
  char c;

  // Was there an Overrun error?
  if((USART1->ISR & USART_ISR_ORE) != 0)
  {
    // Yes, clear it 
    USART1->ICR |= USART_ICR_ORECF;
  }

  // Wait for data in the Receive Data Register
  while((USART1->ISR & USART_ISR_RXNE) == 0) ;

  // Read data from RDR, clears the RXNE flag
  c = (char)USART1->RDR;

  return(c);
}

void USART_getstr(char *str)
{
	char c;
	
	
	c = 0;
  // Wait for data in the Receive Data Register
	while(c !=  '\r'){
		c = USART_getc();
		*str = c;
		USART_putc(*str);
		str++;
	}
	*str = '\0';
  // Read data from RDR, clears the RXNE flag
  //c = (char)USART1->RDR;
  // Implement this function yourself
}

// Implements the following VT100 terminal commands
// - Clear screan
// - Cursor home
void USART_clearscreen(void)
{
  char cmd1[5] = {0x1B, '[', '2', 'J', '\0'}; // Clear screen
  char cmd2[4] = {0x1B, '[', 'f', '\0'}; // Cursor home
  
  USART_putstr(cmd1);
  USART_putstr(cmd2);
}
