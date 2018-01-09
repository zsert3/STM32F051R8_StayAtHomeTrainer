#include "helper.h"

/**
  * @brief  This function implements a delay.
  *         If the optimization level is set to -O3, this function takes 8
  *         cycles. To create a delay of 1 second, use the following function
  *         call: Delay(SystemCoreClock/8);
  * @param  d: number delay loops (1 loop takes 8/SystemCoreClock sec.)
  * @retval None
  */
void Delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}

void Delay2(const int d)
{
	//delay for < 1 seconds, should be called multiple times for delays larger than 1 second
	
	volatile int i;
	volatile int b = d;
	
	while(b > 0){
		if(b >= 1000){
			for(i=(SystemCoreClock / 8 ); i>0; i--){ ; }
		}
		else{
			for(i=(SystemCoreClock / 8 / (1000 / d)); i>0; i--){ ; }
		}
		b -= 1000;
	}
  return;
}

//void addData(uint16_t *i, average *sumData, uint16_t currentRPM, uint16_t currentTorgue, uint16_t currentPower, uint16_t currentAngle, uint16_t currentSymmetry)
//{
//	
//}

void initTimeoutTIM(){
	TIM_TimeBaseInitTypeDef TIM_initStruct;
	NVIC_InitTypeDef        NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//Timer settings 
	TIM_initStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_initStruct.TIM_Period      = 40000-1;	//20000
  TIM_initStruct.TIM_Prescaler   = (uint16_t)((SystemCoreClock / 100) - 1);
	
	TIM_TimeBaseInit(TIM2, &TIM_initStruct);
	
	//Interrupt settings
	NVIC_InitStructure.NVIC_IRQChannel         = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	

	
}

