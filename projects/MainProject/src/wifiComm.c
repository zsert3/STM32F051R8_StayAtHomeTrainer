/**
******************************************************************************
* @file    	coderingStandaard.h 
* @author 	Example Example
* @version	V0.0.1
* @date   	?? - ?? - ????
* @brief  	Dit is een bestand met daarin voorbeelden van hoe de code 
*			er uit moet zien. (leg uit in het kort wat dit bestand doet)
******************************************************************************
*/

char buf[100];
extern volatile char *buffer;
extern volatile int 	head, tail, ok, fail, sFail,lastBuffer, bufferVal;

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
	
	while(ok == 0){
		if(fail == 1){
			USART_putstr(USART1, "Connect with WIFI Failed!!\r\n");
			WIFI_connect();
		}
	}
}

void WIFI_checkIP(void){
	USART_putstr(USART2, "AT+CIFSR\r\n");
}

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

void WIFI_HTTPPost(uint8_t idRevaladitie, char* startDatum, char* startTijd, uint16_t fietsTijd, uint16_t intensiteit){
	char contentLength[128];
	char sendString[512];
	char bufMessage[512];
	char bufCommand[20];
	
	sprintf(sendString, "idT=0&idRT=%d&startTijd=%s %s&fTijd=%d&intensiteit=%d\r\n", idRevaladitie, startDatum, startTijd, fietsTijd, intensiteit);
	sprintf(contentLength, "Content-length:%d\r\n", strlen(sendString)-2);	//-2 omdat \r\n niet mee telt
	
	strcpy(bufMessage,"POST /add_data.php HTTP/1.1\r\n");
	strcat(bufMessage,"Host: stayathometrainer.nl\r\n");
	strcat(bufMessage,"Content-Type:application/x-www-form-urlencoded\r\n");
	strcat(bufMessage,"Cache-Control:no-cache\r\n");
	strcat(bufMessage, contentLength);
	strcat(bufMessage,"\r\n");
	strcat(bufMessage, sendString);
	
	sprintf(bufCommand, "AT+CIPSENDBUF=%d\r\n", strlen(bufMessage));
	USART_putstr(USART2, bufCommand);
	delay(SystemCoreClock/(8));
	USART_putstr(USART2, bufMessage);
}

void WIFI_checkConnection(void){
	USART_putstr(USART2, "AT+CIPSTATUS\r\n");
	
	
}

void WIFI_init(void){
	USART_putstr(USART1, "----------Start Init--------\r\n");
	
	WIFI_checkConnection();
	while(bufferVal != '3'){	//verbinding met wifi en server
		if(bufferVal == '5'){		//geen verbinding
			WIFI_connect();
			WIFI_connectServer();
			break;
		}else if(bufferVal == '2' || bufferVal == '4'){	//geen verbinding met server, wel met wifi
			WIFI_connectServer();
			break;
		}
	}
	
	
	USART_putstr(USART1, "---------Init Done--------\r\n");
	STM_EVAL_LEDOn(LED3);
}

void delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}

