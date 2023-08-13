/*
 * led.h
 *
 *  Created on: Aug 2, 2023
 *      Author: mehmet.tartan
 */

#pragma once

#define GPIODEN                 (1U<<3)
#define PIN12                   (1U<<12)
#define LED_PIN                 PIN12
#define PIN13                   (1U<<13)
#define LED_PIN1                 PIN13

void led_init();
void led_on();
void led_off();
void led_toggle();
