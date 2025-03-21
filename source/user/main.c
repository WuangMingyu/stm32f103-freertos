#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"                    // RTOS header
#include "task.h"                        // RTOS task header


TaskHandle_t myTaskHandle;

void mytask(void *param)
{
}
int main(void)
{
	xTaskCreate(mytask, "mytask", 1000, NULL, 1, &myTaskHandle);
	vTaskStartScheduler();
	while(1)
	{
	}
}
