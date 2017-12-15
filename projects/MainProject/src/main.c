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

extern volatile char *buffer;
extern volatile int head, tail;


int main(){
	char buf[128];
	
	buffer = malloc(101 * sizeof(*buffer));
	head = 0;
	tail = 0;
	
	if (!buffer) {
	//error
	return 1; //return with failure
	}
	
	USART_init();
	STM_EVAL_LEDInit(LED3);
	// Initialize User Button on STM32F0-Discovery
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	WIFI_init();
	
	while(1){
		
		//sendATCommand();
		//STM_EVAL_LEDOn(LED3);
		//USART_getc(USART1);	//print to usart1
		
		//STM_EVAL_LEDOff(LED3);
		if (STM_EVAL_PBGetState(BUTTON_USER))
    {
			STM_EVAL_LEDOn(LED3);
			
			delay(SystemCoreClock/8);
			WIFI_sendCommand("USER n2jsq3g55axh\r\n\r\n");
			delay(SystemCoreClock/4);
			WIFI_sendCommand("PASS aKGEW6!#\r\n\r\n");
			//WIFI_sendCommand("GET /HTTP/1.1\r\nstayathometrainer.nl/inloggen.php\r\n\r\n");
    }
    else
    {
      STM_EVAL_LEDOff(LED3);
    }
		
		
	}
}


