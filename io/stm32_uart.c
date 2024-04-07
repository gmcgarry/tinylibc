#include <stdint.h>

#define __I	volatile
#define __IO	volatile
#define __IOM	volatile

#include "stm32f103x6.h"

static void
USART1_init(uint32_t baudrate)
{
	// enable clock for GPIOA and USART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

	// reset pin configurations for PA9 and PA10
	GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF9);

	// PA9 as Output@50Hz Alternate function
	GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;

	// PA10 as floating input
	GPIOA->CRH |= GPIO_CRH_CNF10_0;

#if 0
	uint32_t baud = (uint32_t)(SystemCoreClock / baudrate);
	USART1->BRR = baud;
#else
	USART1->BRR = 8000000 / 9600;
#endif

	  USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

static void
USART1_putch(char c)
{
	while (!(USART1->SR & USART_SR_TXE))
		;
	USART1->DR = 0x000000ff & c;
}

static char
USART1_getch(void)
{
	return 0;
}


void
__libc_init()
{
	USART1_init(9600);
}

void
putch(int c)
{
	USART1_putch(c);
}

int
getch()
{
	return USART1_getch();
}

int
getche()
{
	int ch = getch();
	putch(ch);
	return ch;
}

int
kbhit(void)
{
	return 0;
}

void
_exit(int c)
{
	while (1)
		;
}
