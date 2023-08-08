#include "stm32f407xx.h"
#include "uart.h"
#include "string.h"

#define GPIOAEN                 (1U<<0)
#define UART2EN                 (1U<<17)

#define CR1_TE                  (1U<<3)
#define CR1_UE                  (1U<<13)
#define SR_TXE                  (1U<<7)

#define SYS_FREQ                16000000
#define APB1_CLK                SYS_FREQ

#define UART_BAUDRATE           115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);


void uart2_tx_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	RCC->APB1ENR |= UART2EN;

	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	USART2->CR1 = CR1_TE;

	USART2->CR1 |= CR1_UE;
}

void uart2_write_char(char ch)
{
	while(! (USART2->SR & SR_TXE)) { }

	USART2->DR = (ch & 0xFF);
}

void uart2_write_string(const char* str) {
    while (*str) {
    	uart2_write_char(*str++);
    }
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, Baudrate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate)
{
	return ((PeriphClk + (Baudrate/2U))/Baudrate);

}










