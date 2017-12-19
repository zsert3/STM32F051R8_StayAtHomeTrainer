
#include "sendReceiveUART.h"
#include "bluetoothComm.h"


void Bluetooth_connect ()
{
		USART_putstr("$$$");
		
		USART_putstr("ST,0");
	
		USART_putstr("SA,0");
	
		USART_putstr("SO,");
	
		USART_putstr("SM,0");
	
		USART_putstr("---");
}