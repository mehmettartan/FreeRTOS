
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "uart.h"


void Task1(void * str)
{
   // size = xPortGetFreeHeapSize();

  for(;;)
  {
        led_toggle();
        uart2_write_string(str);
        vTaskDelay(1200);

  }


}
void Task2(void * str)
{



  /* Infinite loop */
  for(;;)
  {
        uart2_write_string(str);
        vTaskDelay(1000);
  }

}


int main(int argc, char **argv)
{
	uart2_tx_init();
	led_init();
	pa0_exti_init();

 	xTaskCreate(Task1,"Task 1",100,(void *)"Task1 is running...\r\n",0,NULL);

    xTaskCreate(Task2,"Task 2",100,(void *)"Task2 is running...\r\n",0,NULL);

    vTaskStartScheduler();

	while(1)
	{

	}
}
















