#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int main(void)
{
	RCC_DeInit(); // SYSCLK = 16MHz, HSI = ON, HSE = OFF
	// Note: We should change 'configCPU_CLOCK_HZ', It'll be 16MHz in 'FreeRTOSConfig.h'

	SystemCoreClockUpdate(); //-> It can do for changing the variable of 'SystemCoreClock'

	while (1)
	{

	}
}












void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
