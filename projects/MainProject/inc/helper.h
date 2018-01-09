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

typedef struct
{
	uint64_t sumRPM ;
	uint64_t sumTorgue;
	uint64_t sumPower;
	uint64_t sumAngle;
	uint64_t sumSymmetry;
}average;

/* Public functions --------------------------------------------------------*/
void Delay(const int d);
void Delay2(const int d);
void addData(uint16_t *i, average *sumData, uint16_t currentRPM, uint16_t currentTorgue, uint16_t currentPower, uint16_t currentAngle, uint16_t currentSymmetry);
void initTimeoutTIM(void);

//average calcAverage(average currentAverage, currentData newData);
/* Public variables --------------------------------------------------------*/
typedef struct
{
    union {    uint16_t value; uint8_t bytes[2]; }duration;
    union {    int16_t value; uint8_t bytes[2]; }averageRPM;
    union {    int16_t value; uint8_t bytes[2]; }averageTorque;
    union {    uint16_t value; uint8_t bytes[2]; }averagePower;
    union {    uint16_t value; uint8_t bytes[2]; }averageAngle;
    union {    uint16_t value; uint8_t bytes[2]; }averageSymmetry;
    union {    uint16_t value; uint8_t bytes[2]; }calories;
    union {    int16_t value; uint8_t bytes[2]; }averagePassiveRPM;
    union {    int16_t value; uint8_t bytes[2]; }minPassiveRPM;
    union {    int16_t value; uint8_t bytes[2]; }maxPassiveRPM;
    union {    int16_t value; uint8_t bytes[2]; }averageDriveTorque;
    union {    int16_t value; uint8_t bytes[2]; }averageDriveTorqueLimit;
    union {    int16_t value; uint8_t bytes[2]; }minDriveTorque;
    union {    int16_t value; uint8_t bytes[2]; }maxDriveTorque;
    union {    int16_t value; uint8_t bytes[2]; }averageBrakeTorque;
    union {    int16_t value; uint8_t bytes[2]; }minBrakeTorque;
    union {    int16_t value; uint8_t bytes[2]; }maxBrakeTorque;
    char trainType[10];
    char trainer[10];
    char deviceMode[10];
}revalidationData;


typedef struct
{
	uint16_t currentRPM;
	uint16_t currentTorgue;
	uint16_t currentPower;
	uint16_t currentAngle;
	uint16_t currentSymmetry;
}currentData;

typedef struct 
{
		union {	uint16_t value; uint8_t bytes[2]; }duration;
		union { uint8_t value; uint8_t bytes[1]; }startDateDD;
		union { uint8_t value; uint8_t bytes[1]; }startDateMM;
		union {	uint16_t value; uint8_t bytes[2]; }startDateYYYY;
		
		union {	uint16_t value; uint8_t bytes[2]; }averageRPM;
		union {	uint16_t value; uint8_t bytes[2]; }averageTorgue;
		union {	uint16_t value; uint8_t bytes[2]; }averagePower;
		union {	uint16_t value; uint8_t bytes[2]; }averageAngle;
		union {	uint16_t value; uint8_t bytes[2]; }averageSymmetry;
		union {	uint16_t value; uint8_t bytes[2]; }calories;
}revalidationData2;

typedef struct
{
	union {	uint16_t value; uint8_t bytes[2]; }tailAdress;
	union {	uint64_t value; uint8_t bytes[8]; }randomData;
}initPage;




#ifdef __cplusplus

}

#endif

#endif /* _helper_H */
