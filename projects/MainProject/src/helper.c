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

