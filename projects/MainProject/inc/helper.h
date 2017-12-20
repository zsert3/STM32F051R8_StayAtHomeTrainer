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

//average calcAverage(average currentAverage, currentData newData);
/* Public variables --------------------------------------------------------*/
typedef struct 
{
	union {	uint16_t value; uint8_t bytes[2]; }duration;
	union { uint32_t value; uint8_t bytes[4]; }intensity;
	union { uint8_t value; uint8_t bytes[1]; }startDateDD;
	union { uint8_t value; uint8_t bytes[1]; }startDateMM;
	union {	uint16_t value; uint8_t bytes[2]; }startDateYYYY;
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
