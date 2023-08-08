
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "led.h"
#include "uart.h"

QueueHandle_t Queue;


void SenderTask(void* str)
{
	uint16_t SendValue;
	vTaskDelay(2000);
	for(int i = 0; i <= 10; i++)
	{
		SendValue = i*10;
		xQueueSendToBack(Queue, &SendValue, pdMS_TO_TICKS(100));
	}

	for(;;)
	{

	}
}

void ReceiverTask(void* str)
{
	BaseType_t status;
	uint16_t received_value;
	char string[50];

	for(;;)
	{
		status = xQueueReceive(Queue, &received_value, pdMS_TO_TICKS(5000));

		if(status == pdPASS)
		{
			sprintf(string, "Received Value: %d\r\n", received_value );
			uart2_write_string(string);
		}
		else
		{
			uart2_write_string("Queue is empty.!\r\n");
		}

	}
}

int main(int argc, char **argv)
{
	uart2_tx_init();
	led_init();


	Queue = xQueueCreate(5, sizeof(uint16_t));

	if(Queue != NULL)
	{
		xTaskCreate(SenderTask, "Sender", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(ReceiverTask, "Receiver", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		vTaskStartScheduler();
	}
	else
	{
		uart2_write_string("Queue Not Created!");
	}

	while(1)
	{

	}
}
















