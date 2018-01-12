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

#include "helper.h"
#include "EEPROM.h"

#include <String.h>
#include <stdlib.h>
#include <stdio.h>

extern volatile char *buffer;
extern volatile uint8_t head, tail;
extern volatile int head, tail; //y u int

//temp debug should be seperate program
#define DEBUG1

extern uint32_t EEPROM_CommStatus;


void sendEepromToWeb(uint16_t tailAdress);
	
//newmain
int main()
{
	//!!!!!!!!!!!!!!!!!
	//changed page write delay to 10ms
	//!!!!!!!!!!!!!!!!!
	initPage initData;
	currentData currentData;
	revalidationData finalData;
	average averageData;
	uint8_t saveEEPROM = 0;
	uint8_t wifiConnectionStatus = 0;
	int64_t sumCount = 0;
	
	multiplexInit();
	selectMultiplex(1); 
	
	//led and button initialization
	STM_EVAL_LEDInit(LED3); 
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	
	//EEPROM initialisation
	I2C_Setup();
	
	//temp debug, should be seperate program
	#ifdef DEBUG
	EEPROM_clearData();
	initData.tail.value = 1;
	initData.idRevTrainer.value = 5;
	initData.ipAdress = "160.153.129.214";
	initData.SSID = "ESP8266";
	initData.pass = "123456789";
	initData.lampMac = "haHAA"
	EEPROM_setInitPage(initData);
	#endif
	
	if(EEPROM_CommStatus != EEPROM_COMM_OK )
	{
		//error state example blink led fast
		 while(1)
      {
        STM_EVAL_LEDToggle(LED3);
        Delay(SystemCoreClock/8/20);
      }
	}
		
	initData = EEPROM_getInitPage();
	
	//select wifi
	
	if(WIFI_init())
	{
		if(initData.tailAdress.value > 1)
			sendEepromToWeb(initData.tailAdress.value);
			initData.tailAdress.value = 1;
			saveEEPROM = 0;
	}
	else
	{
		saveEEPROM = 1;
	}
		
	//select koning Harald Blauwtand van Denemarken
	while(1)
	{
		
		//read bluetooth data
		//currentData = gerardbleutoothmagie
		
		sumCount++;
		
		averageData.sumRPM += currentData.currentRPM;
 		averageData.sumTorque += currentData.currentTorque;
		averageData.sumPower += currentData.currentPower;
		averageData.sumAngle += currentData.currentAngle;
		averageData.sumSymmetry += currentData.currentSymmetry;
		averageData.sumPassiveRPM += currentData.passiveRPM;
		averageData.sumDriveTorque += currentData.driveTorque;
		averageData.sumDriveTorqueLimit += currentData.driveTorqueLimit;
		averageData.sumBrakeTorque += currentData.brakeTorque;
		
		//send current rpm to lamp
		//BlueToothLamp_setValue(currentRPM)
		
		//detected revalidation ended
		if(currentData.remainingTime == -1)
		{ 
			finalData.duration.value = 12; //total time variable
			finalData.averageRPM.value = (int16_t)(averageData.sumRPM / sumCount);
			finalData.averageTorque.value = (int16_t)(averageData.sumTorque / sumCount);
			finalData.averagePower.value = (uint16_t)(averageData.sumPower / sumCount);
			finalData.averageAngle.value = (uint16_t)(averageData.sumAngle / sumCount);
			finalData.averageSymmetry.value = (uint16_t)(averageData.sumSymmetry / sumCount);
			finalData.calories.value = currentData.calories;
			finalData.averagePassiveRPM.value = (int16_t)(averageData.sumPassiveRPM / sumCount);
			finalData.minPassiveRPM.value = currentData.minPassiveRPM;
			finalData.maxPassiveRPM.value = currentData.maxPassiveRPM;
			finalData.averageDriveTorque.value = (int16_t)(averageData.sumDriveTorque / sumCount);
			finalData.averageDriveTorqueLimit.value = (int16_t)(averageData.sumDriveTorqueLimit / sumCount);
			finalData.minDriveTorque.value = currentData.minPassiveRPM;
			finalData.maxDriveTorque.value = currentData.maxDriveTorque;
			finalData.averageBrakeTorque.value = (int16_t)(averageData.sumBrakeTorque / sumCount);
			finalData.minBrakeTorque.value = currentData.minBrakeTorque;
			finalData.maxBrakeTorque.value = currentData.maxBrakeTorque;
		  strcpy(finalData.trainType, currentData.trainType);
			strcpy(finalData.trainer, currentData.trainer);
			strcpy(finalData.deviceMode, currentData.deviceMode);


			//select wifi
			//wifiConnectionStatus = WIFI_init(); //wifi init returns true instantly if the connection is still active
		
			if(wifiConnectionStatus)
			{
				//HTTPPost(finalData);
				if(initData.tailAdress.value > 1)
				{
					sendEepromToWeb(initData.tailAdress.value);
					initData.tailAdress.value = 1;
				}
			}
			else
			{
				EEPROM_setRevalidationData(initData.tailAdress.value  , finalData);
				initData.tailAdress.value++;
			}
		}
	}
}


void sendEepromToWeb(uint16_t tailAdress)
{
	uint16_t i = 1;
	
	for(i = 1; i < tailAdress; i++)
	{
		WIFI_HTTPPost(EEPROM_getRevalidationData(i));
	}
}


