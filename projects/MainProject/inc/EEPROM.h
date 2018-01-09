/**
******************************************************************************
* @file    	EEPROM.h 
* @author 	
* @version	V0.0.1
* @date   	?? - ?? - ????
* @brief  	
******************************************************************************
*/
  
#ifndef _EEPROM_H
#define _EEPROM_H
  
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"
#include "helper.h"
#include <stdlib.h>
#include <stdio.h>
	#include "string.h"
	
//device 7-bits address assuming A0=A1=A2=0
#define EEPROM_ADDR               0xA0
	
// Maximum timeout value for waiting loops
// This timeout is not based on an accurate timing value. It just guarantess
// that the program will not get stuck in an endless loop whenever there is an
// error in the I2C communication
#define EEPROM_TIMEOUT            ((uint32_t)(0x00001000))

// EEPROM communication status information
#define EEPROM_COMM_OK            (0x0)
#define EEPROM_COMM_ERROR         (0x1)
	
/* Public functions --------------------------------------------------------*/
void    					I2C_Setup( void );
void    					SE24LC512_Clear(void);
initPage 					EEPROM_getInitPage(void); 
void 							EEPROM_setInitPage(initPage page);
void 							EEPROM_setRevalidationData(uint16_t addr, revalidationData data);
revalidationData 	EEPROM_getRevalidationData(uint16_t addr);
/* Public variables --------------------------------------------------------*/

#ifdef __cplusplus

}

#endif

#endif /* _EEPROM_H */
