#include "stm32f4xx.h"
#include "led.h"

void led_init()
{
	RCC->AHB1ENR |= GPIODEN;

	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &=~(1U<<25);
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);
}

void led_on()
{
	GPIOD->BSRR = LED_PIN;
	GPIOD->BSRR = LED_PIN1;

}

void led_off()
{
	GPIOD->BSRR = (1U<<28);
	GPIOD->BSRR = (1U<<29);
}

void led_toggle()
{
	HAL_GPIO_TogglePin(GPIOD, LED_PIN);
	HAL_GPIO_TogglePin(GPIOD, LED_PIN1);
}


