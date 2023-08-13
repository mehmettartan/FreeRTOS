
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "led.h"
#include "uart.h"
#include "exti.h"

SemaphoreHandle_t BinarySem;

void Task1(void * argument)
{
	for(;;)
	{
		uart2_write_string("Task1 is running...\r\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void HandlerTask(void * argument)
{
	for(;;)
	{
		xSemaphoreTake(BinarySem, portMAX_DELAY);
		uart2_write_string("Handler Task is running...\r\n");
		led_toggle();
	}
}

void EXTI0_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uart2_write_string("ISR is running..!\r\n");
	xSemaphoreGiveFromISR(BinarySem, &xHigherPriorityTaskWoken);
	EXTI->PR |= LINE0;
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

int main(int argc, char **argv)
{

	pa0_exti_init();
	uart2_tx_init();
	led_init();

	BinarySem = xSemaphoreCreateBinary();

	xTaskCreate(Task1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(HandlerTask, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();

	while(1)
	{

	}
}

