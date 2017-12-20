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

#include <String.h>
#include <stdlib.h>
#include <stdio.h>

extern volatile char *buffer;
extern volatile int head, tail;


int main(){	
	uint8_t idRevaladitie = 3;
	char startDatum[128] = "2017-02-5";
	char startTijd[128] = "12-23-00";
	uint16_t fietsTijd = 32450;
	uint16_t intensiteit = 900;
	
	buffer = malloc(101 * sizeof(*buffer));
	head = 0;
	tail = 0;
	

	
	USART_init();
	STM_EVAL_LEDInit(LED3);
	// Initialize User Button on STM32F0-Discovery
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	
	WIFI_init();
	
	while(1){

		if (STM_EVAL_PBGetState(BUTTON_USER))
    {
			
			STM_EVAL_LEDOff(LED3);
			Delay(SystemCoreClock/8);
			
			WIFI_HTTPPost(idRevaladitie, startDatum, startTijd, fietsTijd, intensiteit);
    }
    else
    {
      STM_EVAL_LEDOn(LED3);
    }
		
		
	}
}


