
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "led.h"
#include "uart.h"
#include "timers.h"


TimerHandle_t Auto_Reload_Timer, One_Shot_Timer;

void OneShotTimerCallback(TimerHandle_t xtimer)
{
	TickType_t Current_Time = xTaskGetTickCount();

	led_toggle();

	char string[50];

	sprintf(string, "One-Shot Timer: %d\r\n", Current_Time);
	uart2_write_string(string);
}

void AutoReloadTimerCallback(TimerHandle_t xTimer)
{
	TickType_t Current_Time = xTaskGetTickCount();

	led_toggle();

	char string[50];

	sprintf(string, "Auto-Reload Timer: %d\r\n", Current_Time);
	uart2_write_string(string);

}


int main(int argc, char **argv)
{
	uart2_tx_init();
	led_init();


	One_Shot_Timer = xTimerCreate("One-Shot", pdMS_TO_TICKS(500), pdFALSE, 0, OneShotTimerCallback);
	Auto_Reload_Timer = xTimerCreate("Auto-Reload-Timer", pdMS_TO_TICKS(700), pdTRUE, 0, AutoReloadTimerCallback);

	xTimerStart(One_Shot_Timer, 0);
	xTimerStart(Auto_Reload_Timer, 0);

	vTaskStartScheduler();

	while(1)
	{

	}
}















