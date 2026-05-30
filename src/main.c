#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

// My Functions
void Task1_Handler(void *params);
void Task2_Handler(void *params);

int main(void)
{
	RCC_DeInit(); // SYSCLK = 16MHz; HSI = ON, HSE = OFF, So PLL = OFF
	// Note: We should change 'configCPU_CLOCK_HZ', It'll be 16MHz in 'FreeRTOSConfig.h'

	SystemCoreClockUpdate(); //-> It can do for changing the variable of 'SystemCoreClock' (So it'll be 16Mhz)

	////// Creating a new task
	xTaskCreate(Task1_Handler, "Görev 1", configMINIMAL_STACK_SIZE, NULL, 4, &myTask1Handle);

	xTaskCreate(Task2_Handler, "Görev 2", configMINIMAL_STACK_SIZE, NULL, 4, &myTask2Handle);

	/*
	 xTaskCreate(
				 	TaskFunction_t pxTaskCode,
					const char * const pcName,
					const configSTACK_DEPTH_TYPE uxStackDepth,
					void * const pvParameters,
					UBaseType_t uxPriority,
					TaskHandle_t * const pxCreatedTask
				)
	 */

	vTaskStartScheduler();

	while (1)
	{

	}
}

/// That's the task1's of function
void Task1_Handler(void *params)
{
	for(;;) // While or For, Either is ok
	{

	}
}

void Task2_Handler(void *params)
{
	while(1) // While or For, Either is ok
	{

	}
}








void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
