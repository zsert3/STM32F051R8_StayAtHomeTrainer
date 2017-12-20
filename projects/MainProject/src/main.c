/**
******************************************************************************
* @file    	main.c
* @author 	Rick Winters
* @version	V0.0.1
* @date   	06-12-2017
* @brief  	This is the main file of the project
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "sendReceiveUART.h"
#include "helper.h"

int main(){
	currentData data;
	revalidationData2 data2;
	revalidationData datading;
	uint16_t i;
	average sum = {0, 0, 0, 0, 0};
	USART_init();
	USART_putc('1');
	//Delay(SystemCoreClock / 8 / 1);
  USART_putc('2');
	//Delay(SystemCoreClock / 8 / 1);
	USART_putc('1');
	//Delay2(2000);
	USART_putc('2');
	
	//initial data
	data2.startDateDD.value = 20;
	data2.startDateMM.value = 12;
	data2.startDateYYYY.value = 2017;
	data2.duration.value = 110; //remaining time
	
	//continuous data (averages)
	data2.calories.value = 333; //can be saved last 
	sum.sumAngle += 10;
	sum.sumRPM += 20;
	sum.sumSymmetry += 60;
	sum.sumPower += 120;
	sum.sumTorgue += 419;
	i++;
	
	//end data
	data2.averageAngle.value = sum.sumAngle / i;
	data2.averagePower.value = sum.sumPower / i;
	data2.averageRPM.value = sum.sumRPM / i;
	data2.averageSymmetry.value = sum.sumSymmetry / i;
	data2.averageTorgue.value = sum.sumTorgue / i;
	
	//Fach[0] = (struct sFach){"Analysis 1","AN 1",0,0.667};
	datading.startDateDD.value = 20;
	datading.startDateMM.value = 12;
	datading.startDateYYYY.value = 2017;
	datading.duration.value = 123;
	datading.intensity.value = 9001;
	
	//i = (revalidationData)datading.[0].value;
		
	while(1)
	{
		
	}
}
