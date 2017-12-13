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
/* Includes ------------------------------------------------------------------*/
#include "sendReceiveUART.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <String.h>
#include <stdio.h>

void delay(const int d);

void sendATCommand(void){
	USART_putstr(USART2, "AT\r\n");
	//USART_putEnter();
}

void WIFI_connect(void){
	USART_putstr(USART2, "AT+CWJAP=\"ESP8266\",\"123456789\"");
	USART_putEnter();
}

void WIFI_checkIP(void){
	USART_putstr(USART2, "AT+CIFSR");
	USART_putEnter();
}

void WIFI_connectServer(void){
	USART_putstr(USART2, "AT+CIPSTART=\"TCP\",\"160.153.129.214\",21");
	USART_putEnter();
}

void WIFI_sendCommand(char* str){
	//niet 4 maar length van str
	char buf[20];
	sprintf(buf, "AT+CIPSEND=%d", strlen(str));
	USART_putstr(USART2, buf);	
	USART_putEnter();
	delay(SystemCoreClock/(8*10));
	USART_putstr(USART2, str);
}


void WIFI_init(void){
	WIFI_connect();
//	delay(SystemCoreClock);
//	WIFI_connectServer();
}

void delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}

