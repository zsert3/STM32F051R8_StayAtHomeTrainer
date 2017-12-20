/**
******************************************************************************
* @file    	main.c
* @author 	Rick Winters
* @version	V0.0.1
* @date   	06-12-2017
* @brief  	This is the main file of the project
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "sendReceiveUART.h"
#include "helper.h"

int main(){
	USART_init();
	USART_putc('1');
	Delay(SystemCoreClock / 8 / 1);
  USART_putc('2');
	Delay(SystemCoreClock / 8 / 1);
	USART_putc('1');
	Delay2(2000);
	USART_putc('2');
}
