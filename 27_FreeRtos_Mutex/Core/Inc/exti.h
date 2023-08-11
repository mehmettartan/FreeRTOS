/*
 * exti.h
 *
 *  Created on: Apr 19, 2023
 *      Author: ubuntu
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f4xx.h"

void pa0_exti_init(void);

#define LINE0         (1U<<0)

#endif /* EXTI_H_ */
