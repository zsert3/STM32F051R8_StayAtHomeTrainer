/**
******************************************************************************
* @file    	main.c
* @author 	Rick Winters, Bastiaan Metz
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
#include "helper.h"
#include "EEPROM.h"

#include <String.h>
#include <stdlib.h>
#include <stdio.h>

extern uint32_t EEPROM_CommStatus;
extern volatile char *buffer;
extern volatile int head, tail;


int main(){	

	revalidationData dataSendRev;
	revalidationData dataRecieveRev;
	//buffer = malloc(101 * sizeof(*buffer));
	head = 0;
	tail = 0;
	
	dataSendRev.duration.value = 600;
	dataSendRev.intensity.value = 20;
	dataSendRev.startDateDD.value = 3;
	dataSendRev.startDateMM.value = 12;
	dataSendRev.startDateYYYY.value = 1996;
	
	
	USART_init();
	STM_EVAL_LEDInit(LED3);
	// Initialize User Button on STM32F0-Discovery
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	
	WIFI_init();
	
	I2C_Setup();
	
	while(1){

		if (STM_EVAL_PBGetState(BUTTON_USER) && EEPROM_CommStatus == EEPROM_COMM_OK)
    {
			
			STM_EVAL_LEDOff(LED3);
			Delay(SystemCoreClock/8);

			USART_putstr(USART1, "Data opslaan in EEPROM...\r\n");
			EEPROM_setRevalidationData(128, dataSendRev);

			
			USART_putstr(USART1, "Data ophalen uit EEPROM...\r\n");
			dataRecieveRev = EEPROM_getRevalidationData(128);

			USART_putstr(USART1, "Data verzenden naar server\r\n");
	
			WIFI_HTTPPost2(dataRecieveRev);
    }
    else
    {
      STM_EVAL_LEDOn(LED3);
    }
		
		
	}
}


