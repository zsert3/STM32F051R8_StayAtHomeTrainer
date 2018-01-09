/**
******************************************************************************
* @file    	wifiComm.h 
* @author 	
* @version	V0.0.1
* @date   	?? - ?? - ????
* @brief  	
******************************************************************************
*/
  
#ifndef _wifiComm_H
#define _wifiComm_H
  
#ifdef __cplusplus
extern "C" {
#endif
	
	#include "stdint.h"
	#include "sendReceiveUART.h"
	#include "sendReceiveUART.h"
	#include "stm32f0xx.h"
	#include "stm32f0_discovery.h"
	#include "helper.h"
	#include <String.h>
	#include <stdio.h>
	
/* Public functions --------------------------------------------------------*/
	void WIFI_init(void);
	void WIFI_reset(void);
	void sendATCommand(void);
	void WIFI_connect(void);
	void WIFI_checkIP(void);
	void WIFI_connectServer(void);
	void WIFI_HTTPPost(revalidationData data);
	uint8_t WIFI_checkConnection(void);

/* Public variables --------------------------------------------------------*/

#ifdef __cplusplus

}

#endif

#endif /* _sendReceiveUART_H */
