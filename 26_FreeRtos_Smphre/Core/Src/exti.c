/*
 * exti.c
 *
 *  Created on: Apr 19, 2023
 *      Author: ubuntu
 */

#include "exti.h"

#define GPIOAEN     (1U<<0)
#define SYSCFGEN     (1U<<14)

void pa0_exti_init(void)
{
	/*Disable global interrupt */
	__disable_irq();

	/*Enable clock access for GPIOC */
	RCC->AHB1ENR |= GPIOAEN;

	/*Enable clock access SysCnfg */
	RCC->APB2ENR |= SYSCFGEN;

	/*Set PA0 as Input	 */
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<1);

	/*Select PORTA for EXTI0 */
	//SYSCFG->EXTICR[3] |= (1U<<5);

	/*UNMASK EXTI13 */
	EXTI->IMR |= (1U<<0);

	/*Select falling edge trigger */
	EXTI->FTSR |= (1U<<0);

	/*Enable EXTI3 line in NVIC */
	NVIC_SetPriority(EXTI0_IRQn, 5);
	NVIC_EnableIRQ(EXTI0_IRQn);

	/*Enable global interrupt */
	__enable_irq();
}
