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

