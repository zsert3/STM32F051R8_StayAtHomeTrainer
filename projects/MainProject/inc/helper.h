/**
******************************************************************************
* @file     helper.h 
* @author 	
* @version	V0.0.1
* @date   	?? - ?? - ????
* @brief  	
******************************************************************************
*/
  
#ifndef _helper_H
#define _helper_H
  
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_tim.h"
#include "stm32f0_discovery.h"
#include <stdlib.h>



/* Public functions --------------------------------------------------------*/
void Delay(const int d);
void Delay2(const int d);

void initTimeoutTIM(void);


/* Public variables --------------------------------------------------------*/

	union {	uint16_t value; uint8_t bytes[2]; }duration;
	union { uint32_t value; uint8_t bytes[4]; }intensity;
	union { uint8_t value; uint8_t bytes[1]; }startDateDD;
	union { uint8_t value; uint8_t bytes[1]; }startDateMM;
	union {	uint16_t value; uint8_t bytes[2]; }startDateYYYY;
}revalidationData2;


typedef struct
{
	int16_t currentRPM;
	int16_t currentTorque;
	uint16_t currentPower;
	uint16_t currentAngle;
	uint8_t currentSymmetry;
	int32_t remainingTime; //kan -1 zijn, wordt ingesteld dus mogelijk groter dan 16 int
	uint16_t calories;
	int16_t passiveRPM;
	int16_t minPassiveRPM;
	int16_t maxPassiveRPM;
	int16_t driveTorque;
	int16_t driveTorqueLimit;
	int16_t minDriveTorque;
	int16_t maxDriveTorque;
	int16_t brakeTorque;
	int16_t minBrakeTorque;
	int16_t maxBrakeTorque;
	char *trainType; //invalid, redDemand
	char *trainer; //invalid, legtrainer
	char *deviceMode; //invalid, start, stop, pause
}currentData;

typedef struct
{
	uint64_t sumRPM ;
	uint64_t sumTorque;
	uint64_t sumPower;
	uint64_t sumAngle;
	uint64_t sumSymmetry;
	int64_t sumPassiveRPM;
}average;


typedef struct
{
	union {	uint16_t value; uint8_t bytes[2]; }duration;
	union {	int16_t value; uint8_t bytes[2]; }averageRPM;
	union {	int16_t value; uint8_t bytes[2]; }averageTorque;
	union {	uint16_t value; uint8_t bytes[2]; }averagePower;
	union {	uint16_t value; uint8_t bytes[2]; }averageAngle;
	union {	uint16_t value; uint8_t bytes[2]; }averageSymmetry;
	union {	uint16_t value; uint8_t bytes[2]; }calories;
	union {	int16_t value; uint8_t bytes[2]; }averagePassiveRPM;
	union {	int16_t value; uint8_t bytes[2]; }minPassiveRPM;
	union {	int16_t value; uint8_t bytes[2]; }maxPassiveRPM;
	union {	int16_t value; uint8_t bytes[2]; }averageDriveTorque;
	union {	int16_t value; uint8_t bytes[2]; }averageDriveTorqueLimit;
	union {	int16_t value; uint8_t bytes[2]; }minDriveTorque;
	union {	int16_t value; uint8_t bytes[2]; }maxDriveTorque;
	union {	int16_t value; uint8_t bytes[2]; }averageBrakeTorque;
	union {	int16_t value; uint8_t bytes[2]; }minBrakeTorque;
	union {	int16_t value; uint8_t bytes[2]; }maxBrakeTorque;
	char trainType[10];
	char trainer[10];
	char deviceMode[10];
}revalidationData;
 

typedef struct
{
	union {	uint16_t value; uint8_t bytes[2]; }tailAdress;
	char IPAdress[20];
	char SSID[15];
	char pass[11]; 
	char lampMAC[15];
}initPage;




#ifdef __cplusplus

}

#endif

#endif /* _helper_H */
