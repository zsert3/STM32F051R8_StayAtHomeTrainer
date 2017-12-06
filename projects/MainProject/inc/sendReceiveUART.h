/**
******************************************************************************
* @file    	sendReceiveUART.h 
* @author 	
* @version	V0.0.1
* @date   	?? - ?? - ????
* @brief  	
******************************************************************************
*/
  
#ifndef _sendReceiveUART_H
#define _sendReceiveUART_H
  
#ifdef __cplusplus
extern "C" {
#endif
	
	#include "stdint.h"
	
/* Public functions --------------------------------------------------------*/
	void USART_init(void);
	void USART_putc(char c);
	char USART_getc(void);
	void USART_putstr(char *str);
	void USART_getstr(char *str);
	void USART_clearscreen(void);

/* Public variables --------------------------------------------------------*/

#ifdef __cplusplus

}

#endif

#endif /* _sendReceiveUART_H */
