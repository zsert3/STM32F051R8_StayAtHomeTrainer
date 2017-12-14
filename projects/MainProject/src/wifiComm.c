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
extern volatile int 	head, tail, OK, FAIL;

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
	USART_putstr(USART2, "AT+CIPSTART=\"TCP\",\"160.153.129.214\",21\r\n");
}

void WIFI_sendCommand(char* str){
	//niet 4 maar length van str
	char buf[20];
	sprintf(buf, "AT+CIPSEND=%d", strlen(str));
	USART_putstr(USART2, buf);	
	USART_putEnter();
	while(OK != 1);
	USART_putstr(USART2, str);
}


void WIFI_init(void){
	USART_putstr(USART1, "---------------------------Start Init---------------------------\r\n");
	
//	WIFI_reset();
//	USART_putstr(USART1, "RESET...\r\n");
//	while(OK != 1);
//	USART_putstr(USART1, "---------------------------RESET DONE------------------\r\n");
	WIFI_connect();
	
	USART_putstr(USART1, "Connecting to WIFI...\r\n");
	
	while(OK != 1){
		//USART_getc(USART1);
		if(FAIL == 1){
			USART_putstr(USART1, "Connect with WIFI Failed!!\r\n");
			WIFI_init();
		}
	}
	delay(SystemCoreClock/(8*100));
	USART_putstr(USART1, "Connecting with server...\r\n");
	WIFI_connectServer();
	while(OK != 1);
	USART_putstr(USART1, "------------------------------Init Done--------------------------------\r\n");
}

void delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}

