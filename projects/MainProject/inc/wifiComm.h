/**
******************************************************************************
* @file    	sendReceiveUART.h 
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
	
/* Public functions --------------------------------------------------------*/
	void WIFI_init(void);
	void sendATCommand(void);
	void WIFI_connect(void);
	void WIFI_checkIP(void);
	void WIFI_connectServer(void);
	void WIFI_sendCommand(char* str);
	void delay();

/* Public variables --------------------------------------------------------*/

#ifdef __cplusplus

}

#endif

#endif /* _sendReceiveUART_H */
