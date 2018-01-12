
#include "sendReceiveUART.h"
#include "bluetoothComm.h"

uint16_t toBestored_number;
uint8_t	 wordNumber;

typedef struct
{
	uint16_t currentRPM;
	uint16_t currentTorgue;
	uint16_t currentPower;
	uint16_t currentAngle;
	uint16_t currentSymmetry;
}currentData;



USART_TypeDef* Bleutooth_USART = USART1;




void Blue_delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}

void bluetoothcomm_config()
{
		
		//USART_putstr(USART1, "AT+IMME?");
		Blue_delay(SystemCoreClock/(4));	
		//USART_putstr(USART1, "AT+TYPE2");
		USART_putstr(USART1,"SA,0\r");
		//USART_putstr(USART1, "AT+RESET");
		Blue_delay(SystemCoreClock/(4));
		//USART_putstr(USART1, "AT+BAUD?");
		USART_putstr(USART1,"SO, \r");
		//USART_putstr(USART1, "AT+NAMEWorkDamnYou");
		Blue_delay(SystemCoreClock/(4));
		//USART_putstr(USART1, "AT+IMME?");
		USART_putstr(USART1,"SM,0\r");
		Blue_delay(SystemCoreClock/(4));
}

void CMD_on(){
	USART_putstr(USART1,"$$$");
	Blue_delay(SystemCoreClock/(4));
	//delay(SystemCoreClock/(8));
}

void CMD_off(){
	USART_putstr(USART1,"R,1\r");
	Blue_delay(SystemCoreClock/(4));	
	USART_putstr(USART1,"---");
	Blue_delay(SystemCoreClock/(4));
}


void bluetoothComm_init()
{
	CMD_on();
	bluetoothcomm_config();
	CMD_off();
	
	
}
