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

/* Includes ------------------------------------------------------------------*/  <-- maximale lengte is dit
#include "coderingStandaard.h"
#include "groupGroup_exampleExample.h"
/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EXAMPLE_EXAMPLE 0xAA
#define GROUP_GROUP__EXAMPLE_EXAMPLE 0xDD // An example of group is: I2C or GPIO
/* Error codes for certain item*/
#define ERROR_ERROR 0x01
#define GROUP_GROUP__ERROR_ERROR 0x02

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
	float typeExample; // example of one line use of comments
	float variationExample1; // each variable wil have it's own line
	float variationExample2;
	writeCertainCode = ((float)x) * 3.14 / 180;	  
	/** Declare variables at te point that you need them in order to improve 
	  * readability. !! (and an example of multiple lines of comments)
	  */
	int i;
	typeExample = typeExample + i;
	#if 0 // use #if 0 & #endif to temporarily disable a block of code
	variationExample1 = variationExample1 + variationExample2;
	#endif
	
	// Don't use a magic number ...
	for (int row = 0; row < 100; row++)
	{
		// ... when you mean a constant.
		for (int col = 0; col < MAX_COL; col++)
		{
			...
		}
	}
}
  
/**
  * @brief  This function enables peripheral clocks on GPIO port A
  * 		and configures PA4 in Analog mode. (example)
  * @note		Extra explanation if needed, multiple notes can
  *				be used.
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






