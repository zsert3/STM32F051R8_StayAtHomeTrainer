/**
  ******************************************************************************
  * @file    coderingStandaard.c 
  * @author  Example Example
  * @version V0.0.1
  * @date    ?? - ?? - ????
  * @brief   leg uit in het kort wat dit bestand doet
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/  <-- maximale lengte is dit
#include "groupGroup_exampleExample.h"
/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define exampleExample 0xAA
#define I2C_exampleExample 0xDD
/* Error codes for certain item*/
#define errorError 0x01
#define groupGroup_errorError 0x02

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t exampleExample[exampleExample]={example_exampleExample, exampleExample};
uint16_t exampleExample[exampleExample];

/* Private function prototypes -----------------------------------------------*/
void configureCertainFunction(void);		// @line xx
void Group_configureCertainFunction(void);	// @line xx
uint16_t exampleExample(uint16_t x);		// @line xx
void configureCertainGPIO(void);			// @line xx

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	  
}
  
/**
  * @brief  This function does certain things
  * @param  x is an variable that is send with the function because reason   
  * @retval the type of return value and description of that must be send back
  */
uint16_t exampleExample(uint16_t x)
{
	float typeExample;
	float variationExample1, variationExample2;
	writeCertainCode = ((float)x) * 3.14 / 180;	  
}
  
/**
  * @brief  This function enables peripheral clocks on GPIO port A
  * 		and configures PA4 in Analog mode. (example)
  * @note		Extra explanation if needed, multiple notes can
				be used.
  * @param  None
  * @retval None
  */
void configureCertainGPIO(void)
{
	/* (1) descibe what you do with this register */
	/* (2) descibe what you do with this register */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (1) */
	GPIOA->MODER |= GPIO_MODER_MODER4; /* (2) */
}






