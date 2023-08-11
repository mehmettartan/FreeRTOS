
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "led.h"
#include "uart.h"

SemaphoreHandle_t UartMutex;

void Task1Function(void* argument)
{
	char message[50];
	int i= 0;

	for(;;)
	{
		sprintf(message, "Task1 is running: %d\r\n", i);
		xSemaphoreTake(UartMutex, portMAX_DELAY);
		uart2_write_string(message);
		xSemaphoreGive(UartMutex);
		i++;
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void Task2Function(void * argument)
{
	char message[50];
	int i = 0;

	for(;;)
	{
		sprintf(message, "Task2 is running: %d\r\n", i);
		xSemaphoreTake(UartMutex, portMAX_DELAY);
		uart2_write_string(message);
		xSemaphoreGive(UartMutex);
		i++;
		vTaskDelay(1000);
	}
}

int main(int argc, char **argv)
{
	uart2_tx_init();
	led_init();

	UartMutex = xSemaphoreCreateMutex();

	xTaskCreate(Task1Function, "Task1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(Task2Function, "Task2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

	vTaskStartScheduler();


	while(1)
	{

	}
}
















