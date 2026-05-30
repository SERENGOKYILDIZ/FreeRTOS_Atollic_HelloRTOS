#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "stdio.h" // for printf

#include "FreeRTOS.h"
#include "task.h"

// For printf
int _write(int32_t file, uint8_t *ptr, int32_t len)
{
	for(int i=0;i<len;i++)
	{
		// That does to writing a char at terminal
		ITM_SendChar((*ptr++));
	}
	return len;
}

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

	printf("Starting RTOS project.\n");
	// You should to open "Serial Wire Viewer" in Debugger
	// So you should to select port 0 in "Configure trace" in SWV Console

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
		printf("TASK - 1\n");
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void Task2_Handler(void *params)
{
	while(1) // While or For, Either is ok
	{
		printf("TASK - 2\n");
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}








void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
