/**
******************************************************************************
* @file    	wifiComm.c
* @author 	Rick Winters
* @version	V0.0.1
* @date   	20-12-2017
* @brief  	All functions associated with wifi communication are in this document
******************************************************************************
*/

/* Global variables ----------------------------------------------------------*/
extern volatile char *buffer;
extern volatile int head, tail, ok, fail, sFail,lastBuffer, bufferVal, returnCode;

/* Includes ------------------------------------------------------------------*/
#include "wifiComm.h"

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  This function will reset the Wifi module
  * @param  None
	* @retval None
  */
void WIFI_reset(void){
	USART_putstr(USART2, "AT+RST\r\n");
	while(ok == 0);
}

/**
  * @brief  This function will send an AT command to check
						if the module is working correctly
  * @param  None
	* @retval None
  */
void sendATCommand(void){
	USART_putstr(USART2, "AT\r\n");
	while(ok == 0);
}

/**
  * @brief  This function will make a connection with the wifi network.
						For now a hard-coded SSID and password.
						It will keep on running untill it has astablished a connection
  * @param  None
	* @retval None
  */
void WIFI_connect(void){
	USART_putstr(USART1, "Connecting to WIFI...\r\n");
	USART_putstr(USART2, "AT+CWJAP=\"ESP8266\",\"123456789\"\r\n");
	
	while(ok == 0){
		if(fail == 1){
			USART_putstr(USART1, "Connect with WIFI Failed!!\r\n");
			WIFI_connect();
		}
	}
}

/**
  * @brief  This function will check for his current IP
  * @param  None
	* @retval None
  */
void WIFI_checkIP(void){
	USART_putstr(USART2, "AT+CIFSR\r\n");
	while(ok == 0);
}

/**
  * @brief  This function will make a connection with the server.
						For now hard-coded TCP address.
						It will keep trying untill it has a connection
  * @param  None
	* @retval None
  */
void WIFI_connectServer(void){
	USART_putstr(USART1, "Connecting with server...\r\n");
	USART_putstr(USART2, "AT+CIPSTART=\"TCP\",\"160.153.129.214\",80\r\n");
	//Server IP: 160.153.129.214
	//Local IP: 145.44.97.217
	while(ok == 0){
		if(sFail == 1){
			USART_putstr(USART1, "Connect with server Failed!!\r\n");
			WIFI_connectServer();
		}
	}
}

/**
  * @brief  This function sends a HTTP post message to the connected server.
						It is still fairly static, the parameters are specific to our database
  * @param  uint8_t idRevaladitie
						char* startDatum
						char* startTijd
						uint16_t fietsTijd
						uint16_t intensiteit
	* @retval None
  */
void WIFI_HTTPPost(uint8_t idRevaladitie, char* startDatum, char* startTijd, uint16_t fietsTijd, uint16_t intensiteit){
	char contentLength[128];
	char sendString[512];
	char bufMessage[512];
	char bufCommand[20];
	
	sprintf(sendString, "idT=0&idRT=%d&startTijd=%s %s&fTijd=%d&intensiteit=%d\r\n", idRevaladitie, startDatum, startTijd, fietsTijd, intensiteit);
	sprintf(contentLength, "Content-length:%d\r\n", strlen(sendString)-2);	//-2 because \r\n doesn't have to be counted
	
	strcpy(bufMessage,"POST /add_data.php HTTP/1.1\r\n");
	strcat(bufMessage,"Host: stayathometrainer.nl\r\n");
	strcat(bufMessage,"Content-Type:application/x-www-form-urlencoded\r\n");
	strcat(bufMessage,"Cache-Control:no-cache\r\n");
	strcat(bufMessage, contentLength);
	strcat(bufMessage,"\r\n");
	strcat(bufMessage, sendString);
	
	sprintf(bufCommand, "AT+CIPSENDBUF=%d\r\n", strlen(bufMessage));
	USART_putstr(USART2, bufCommand);
	Delay(SystemCoreClock/(8));
	USART_putstr(USART2, bufMessage);
}

/**
  * @brief  This function returns the state of the Wifi connection
  * @param  None
	* @retval 0: Error state
						1: Wifi connected and server
						2: Wifi connected, Server disconnected
						3: Wifi disconnected
  */
uint8_t WIFI_checkConnection(void){
	USART_putstr(USART2, "AT+CIPSTATUS\r\n");
	//CIPSTATUS returns the state after it sends STATUS:
	
	while(returnCode == 0);	//waiting for : after STATUS

	if(returnCode == '3'){	//Wifi connected and serverr
		USART_putstr(USART1, "Check connection = 1\r\n");
		return 1;
	}else if(returnCode == '5'){	//Wifi disconnected
		USART_putstr(USART1, "Check connection = 3\r\n");
		return 3;
	}else if(returnCode == '2' || bufferVal == '4'){	//Wifi connected, Server disconnected
		USART_putstr(USART1, "Check connection = 2\r\n");
		return 2;
	}else{
		USART_putstr(USART1, "Check connection = ERROR\r\n");
		return 0;	//Error
	}
	
}

/**
  * @brief  This function initialises a connection with wifi and the server.
						The init will only be called once in the main function.
  * @param  None
	* @retval None
  */
void WIFI_init(void){
	uint8_t retVal=0;
	USART_putstr(USART1, "----------Start Init--------\r\n");
	retVal = WIFI_checkConnection();
	
	if(retVal == 3){		//No connection
		WIFI_connect();
		WIFI_connectServer();
	}else if(retVal == 2){	//Wifi connected, Server disconnected
		WIFI_connectServer();
	}
	
	USART_putstr(USART1, "---------Init Done--------\r\n");
	STM_EVAL_LEDOn(LED3);
}



