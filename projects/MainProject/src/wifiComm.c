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
#include "sendReceiveUART.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <String.h>
#include <stdio.h>

void delay(const int d);

void WIFI_reset(void){
	USART_putstr(USART2, "AT+RST\r\n");
}

void sendATCommand(void){
	USART_putstr(USART2, "AT\r\n");
}

void WIFI_connect(void){
	USART_putstr(USART1, "Connecting to WIFI...\r\n");
	USART_putstr(USART2, "AT+CWJAP=\"ESP8266\",\"123456789\"\r\n");
}

void WIFI_checkIP(void){
	USART_putstr(USART2, "AT+CIFSR\r\n");
}

void WIFI_connectServer(void){
	USART_putstr(USART1, "Connecting with server...\r\n");
	USART_putstr(USART2, "AT+CIPSTART=\"TCP\",\"160.153.129.214\",80\r\n");
	//Server IP: 160.153.129.214
	//Local IP: 145.44.97.217
}

void WIFI_sendCommand(char* str){
	//niet 4 maar length van str
	char buf[20];
	sprintf(buf, "AT+CIPSENDBUF=%d\r\n", strlen(str));
	USART_putstr(USART2, buf);
	delay(SystemCoreClock/(8));
	USART_putstr(USART2, str);
	USART_putEnter();
}

void WIFI_checkConnection(void){
	USART_putstr(USART2, "AT+CIPSTATUS\r\n");
	
	
}

void WIFI_init(void){
	USART_putstr(USART1, "----------Start Init--------\r\n");
	
	WIFI_checkConnection();
	while(bufferVal != '3'){
		if(bufferVal == '5'){
			WIFI_connect();
			while(ok == 0){
				if(fail == 1){
					USART_putstr(USART1, "Connect with WIFI Failed!!\r\n");
					WIFI_connect();
				}
			}
			WIFI_connectServer();
			while(ok == 0){
				if(sFail == 1){
					USART_putstr(USART1, "Connect with server Failed!!\r\n");
					WIFI_connectServer();
				}
			}
			break;
		}else if(bufferVal == '2' || bufferVal == '4'){
			WIFI_connectServer();
			while(ok == 0){
				if(sFail == 1){
					USART_putstr(USART1, "Connect with server Failed!!\r\n");
					WIFI_connectServer();
				}
			}
			break;
		}
	}
	
	
	USART_putstr(USART1, "---------Init Done--------\r\n");
}

void delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}

/* Private function prototypes -----------------------------------------------*/
void delay(const int d);
uint8_t WIFI_connectAttempt(void);
/**
  * @brief  This function will reset the Wifi module
  * @param  None
	* @retval None
  */
void WIFI_reset(void){
	USART_putstr(USART2, "AT+RST\r\n");
	USART_getstr("OK");
}

/**
  * @brief  This function will send an AT command to check
						if the module is working correctly
  * @param  None
	* @retval None
  */
void sendATCommand(void){
	USART_putstr(USART2, "AT\r\n");
	USART_getstr("OK");
}

/**
  * @brief  This function will make a connection with the wifi network.
						For now a hard-coded SSID and password.
						It will keep on running untill it has astablished a connection
  * @param  None
	* @retval 1 = succes
						0 = fail
  */
uint8_t WIFI_connect(void){
	uint8_t attempts = 5;
	uint8_t i;
	
	for(i=0;i<5;i++){
		if(WIFI_connectAttempt()){
			return 1;
		}
	}
	
	return 0;
}

uint8_t WIFI_connectAttempt(void){
	USART_putstr(USART1, "Connecting to WIFI...\r\n");
	USART_putstr(USART2, "AT+CWJAP=\"ESP8266\",\"123456789\"\r\n");
	
	if(!USART_getstr("OK")){
		USART_putstr(USART1, "Connect with wifi Failed!!\r\n");
		return 0;
	}
	return 1;
}

/**
  * @brief  This function will check for his current IP
  * @param  None
	* @retval None
  */
void WIFI_checkIP(void){
	USART_putstr(USART2, "AT+CIFSR\r\n");
	USART_getstr("OK");
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
	if(USART_getstr("OK") == 1){
	}else{
		USART_putstr(USART1, "Connect with server Failed!!\r\n");
		WIFI_connectServer();
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


void WIFI_HTTPPost(revalidationData data)
{
	uint16_t length, oldLength, totalLength;
	//char *contentLength;
	char *bufMessage;
	char *bufCommand;
	//char *sendString;
	//char *startString;
	char HTTPBody[270];
	char buf[10];
	//create safespace for arrays
	//contentLength = malloc(20 * sizeof(char));
	//sendString = 		malloc(400 * sizeof(char));

	bufMessage = 		malloc(330 * sizeof(char));
	
	strcpy(bufMessage,"POST /add_data.php HTTP/1.1\r\n");
	strcat(bufMessage,"Host: stayathometrainer.nl\r\n");
	strcat(bufMessage,"Content-Type:application/x-www-form-urlencoded\r\n");
	strcat(bufMessage,"Cache-Control:no-cache\r\n");
	
	//HTTPBody = 			malloc(200 * sizeof(char));

	//sprintf(contentLength, "Content-length:%d\r\n", 225);	//-2 because \r\n doesn't have to be counted
	
	//USART_putstr(USART1, sendString);
	
	//USART_putstr(USART1, contentLength);
	
	//USART_putstr(USART1, startString);
	//strcat(bufMessage, contentLength);
	//free(contentLength);
	//strcat(bufMessage,"\r\n");
	//USART_putstr(USART1, bufMessage);
	oldLength = strlen(bufMessage);
	length = 0;
	
	length += sprintf(HTTPBody+length, "v1=%d&v2=%d&v3=%d&v4=%d&v5=%d&",
												4, data.duration.value, data.averageRPM.value, data.averageTorque.value, data.averagePower.value);
	length += sprintf(HTTPBody+length, "v6=%d&v7=%d&v8=%d&v9=%d&v10=%d&",
										data.averageAngle.value, data.averageSymmetry.value, data.calories.value, data.averagePassiveRPM.value,
										data.minPassiveRPM.value);
	length += sprintf(HTTPBody+length, "v11=%d&v12=%d&v13=%d&v14=%d&",
										data.maxPassiveRPM.value, data.averageDriveTorque.value, data.averageDriveTorqueLimit.value,
										data.minDriveTorque.value);
	length += sprintf(HTTPBody+length, "v15=%d&v16=%d&v17=%d&",
										data.maxDriveTorque.value, data.averageBrakeTorque.value, data.minBrakeTorque.value);
	length += sprintf(HTTPBody+length, "v18=%d&v19=%s&v20=%s&v21=%s\r\n",
										data.maxBrakeTorque.value, data.trainType, data.trainer, data.deviceMode);
	USART_putstr(USART1, HTTPBody);
	
	

	
	
	sprintf(bufMessage+strlen(bufMessage), "Content-length:%d\r\n\r\n%s",length-2, HTTPBody);	//-2 because \r\n doesn't have to be counted
	free(HTTPBody);
	//free(startString);
	//strncat(bufMessage, contentLength, 129);
	
	//USART_putstr(USART1, bufMessage);
	bufCommand = 		malloc(30 * sizeof(char));
	sprintf(bufCommand, "AT+CIPSENDBUF=%d\r\n", strlen(bufMessage));
	USART_putstr(USART2, bufCommand);
	delay(SystemCoreClock/(8));
	USART_putstr(USART2, bufMessage);
	
	//free willy
	free(bufMessage);
	free(bufCommand);
	free(HTTPBody);
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

	if(returnCode == '3'){	//Wifi connected and server
		USART_putstr(USART1, "Check connection = 1\r\n");
		return 1;
	}else if(returnCode == '5' || returnCode == '4'){	//Wifi disconnected
		USART_putstr(USART1, "Check connection = 3\r\n");
		return 3;
	}else if(returnCode == '2'){	//Wifi connected, Server disconnected
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
uint8_t WIFI_init(void){
	uint8_t retVal=0;
	uint8_t status;
	USART_putstr(USART1, "----------Start Init--------\r\n");
	retVal = WIFI_checkConnection();
	
	if(retVal == 3){		//No connection
		if(WIFI_connect() == 1){
			WIFI_connectServer();
		} else{
			return 0;
		}
	}else if(retVal == 2){	//Wifi connected, Server disconnected
		WIFI_connectServer();
	}
	
	USART_putstr(USART1, "---------Init Done--------\r\n");
	STM_EVAL_LEDOn(LED3);
	
	return 1;
}



