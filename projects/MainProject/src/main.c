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
#include "stm32f0xx.h"
#include "sendReceiveUART.h"
#include "stm32f0xx_usart.h"
#include "wifiComm.h"
#include "stm32f0_discovery.h"

#include "bluetoothComm.h"
#include "bluetooth_stringSorter.h"

#include <String.h>
#include <stdlib.h>
#include <stdio.h>

extern volatile char *buffer;
extern volatile uint8_t head, tail;

int main(){
//	char buf[128];
	int i = 0;
	
	buffer = malloc(101 * sizeof(char));

	
	if (!buffer) {
	//error
	return 1; //return with failure
	}
	
	
	USART_init();
	STM_EVAL_LEDInit(LED3);
	// Initialize User Button on STM32F0-Discovery
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	
	bluetoothComm_init();
	presetStringSort();
	USART_putc(USART2, 'N');
	while(1){
		//for(i=SystemCoreClock/8/ (10000); i>0; i--){;}
		if(tail != head)
		{
			sortStringData();
		}

		

		
		
	}
}


