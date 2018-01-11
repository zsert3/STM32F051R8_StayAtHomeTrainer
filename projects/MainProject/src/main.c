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
#include "helper.h"
#include "EEPROM.h"
#include <String.h>
#include <stdlib.h>
#include <stdio.h>

extern uint32_t EEPROM_CommStatus;
extern volatile int head, tail;


int main(){	

	revalidationData dataSendRev;
	//revalidationData dataRecieveRev;
	head = 0;
	tail = 0;
	
	dataSendRev.duration.value = 600;
	dataSendRev.averageAngle.value = 2;
	dataSendRev.averageBrakeTorque.value = 3;
	dataSendRev.averageDriveTorque.value = 4;
	dataSendRev.averageDriveTorqueLimit.value = 5;
	dataSendRev.averagePassiveRPM.value = 6;
	dataSendRev.averagePower.value = 7;
	dataSendRev.averageRPM.value = 8;
	dataSendRev.averageSymmetry.value = 9;
	dataSendRev.averageTorque.value = 10;
	dataSendRev.calories.value = 11;
	strcpy(dataSendRev.deviceMode, "tekst");
	dataSendRev.maxBrakeTorque.value = 13;
	dataSendRev.maxDriveTorque.value = 14;
	dataSendRev.maxPassiveRPM.value = 15;
	dataSendRev.minBrakeTorque.value = 16;
	dataSendRev.minDriveTorque.value = 17;
	dataSendRev.minPassiveRPM.value = 18;
	strcpy(dataSendRev.trainer, "THERA");
	strcpy(dataSendRev.trainType, "SPRINTER");
	
	
	USART_init();
	STM_EVAL_LEDInit(LED3);
	// Initialize User Button on STM32F0-Discovery
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	
	initTimeoutTIM();
	WIFI_init();
	
	I2C_Setup();
	while(1){

		if (STM_EVAL_PBGetState(BUTTON_USER) && EEPROM_CommStatus == EEPROM_COMM_OK)
    {

			STM_EVAL_LEDOff(LED3);
			
//			USART_putstr(USART2, "begin\r\n");
//			USART_putc(USART2, USART_getstr("HOI"));
//			sendATCommand();
			
//			USART_putstr(USART1, "Data opslaan in EEPROM...\r\n");
//			EEPROM_setRevalidationData(128, dataSendRev);
//			
//			USART_putstr(USART1, "Data ophalen uit EEPROM...\r\n");
//			dataRecieveRev = EEPROM_getRevalidationData(128);

			USART_putstr(USART1, "Data verzenden naar server\r\n");
	
			WIFI_HTTPPost(dataSendRev);
			
			Delay(SystemCoreClock/8);

    }
    else
    {
      STM_EVAL_LEDOn(LED3);
    }
		
		
	}
}


