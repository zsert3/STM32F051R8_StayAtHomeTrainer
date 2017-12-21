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
	#include "stm32f0xx_usart.h"
	#include <String.h>
	
/* Public functions --------------------------------------------------------*/
	void USART_init(void);
	void USART_putEnter(void);
	void USART_putc(USART_TypeDef* USARTx, char c);
	void USART_getc(USART_TypeDef* USARTx);
	void USART_putstr(USART_TypeDef* USARTx, char *str);
	char* USART_getstr(USART_TypeDef* USARTx, char *str);
	void USART_clearscreen(USART_TypeDef* USARTx);

/* Public variables --------------------------------------------------------*/

#ifdef __cplusplus

}

#endif

#endif /* _sendReceiveUART_H */
