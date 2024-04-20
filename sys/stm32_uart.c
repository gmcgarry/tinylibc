#include <stdint.h>

#include "STM32F100.h"

#ifndef F_PCLK2
#define F_PCLK2		8000000
#endif

#define	USART_SR_RXNE		((uint32_t)0x00000020)		/*!< Read Data Register Not Empty */
#define	USART_SR_TXE		((uint32_t)0x00000080)		/*!< Transmit Data Register Empty */

#define	USART_CR1_SBK		((uint32_t)0x00000001)		/*!< Send Break */
#define	USART_CR1_RWU		((uint32_t)0x00000002)		/*!< Receiver wakeup */
#define	USART_CR1_RE		((uint32_t)0x00000004)		/*!< Receiver Enable */
#define	USART_CR1_TE		((uint32_t)0x00000008)		/*!< Transmitter Enable */
#define	USART_CR1_IDLEIE	((uint32_t)0x00000010)		/*!< IDLE Interrupt Enable */
#define	USART_CR1_RXNEIE	((uint32_t)0x00000020)		/*!< RXNE Interrupt Enable */
#define	USART_CR1_TCIE		((uint32_t)0x00000040)		/*!< Transmission Complete Interrupt Enable */
#define	USART_CR1_TXEIE		((uint32_t)0x00000080)		/*!< PE Interrupt Enable */
#define	USART_CR1_PEIE		((uint32_t)0x00000100)		/*!< PE Interrupt Enable */
#define	USART_CR1_PS		((uint32_t)0x00000200)		/*!< Parity Selection */
#define	USART_CR1_PCE		((uint32_t)0x00000400)		/*!< Parity Control Enable */
#define	USART_CR1_WAKE		((uint32_t)0x00000800)		/*!< Wakeup method */
#define	USART_CR1_M		((uint32_t)0x00001000)		/*!< Word length */
#define	USART_CR1_UE		((uint32_t)0x00002000)		/*!< USART Enable */

void
USART1_init(uint32_t baudrate)
{
	__enable_peripheral(IOPAEN);					/* enable clock for GPIOA and USART1 */
	__gpio_conf_bit(GPIOA, 9, ALT_PP);				/* PA9 as Output@50Hz Alternate function */
	__gpio_conf_bit(GPIOA, 10, IN_HIZ);				/* PA10 as floating input */

	__enable_peripheral(USART1EN);					/* Enable USART module */
	__reset_peripheral(USART1EN);					/* Reset USART module */

	USART1_BRR = F_PCLK2 / baudrate;				/* Set bit rate */
	USART1_CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;	/* Enable USART in N81 */
}

static void
USART1_putch(char c)
{
	while (!(USART1_SR & USART_SR_TXE))
		;
	USART1_DR = 0x000000ff & c;
}

static char
USART1_getch(void)
{
	while (!(USART1_SR & USART_SR_RXNE))
		;
	char c = USART1_DR;
	return c;
}

void
putch(int c)
{
	if (c == '\n') USART1_putch('\r');
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
	return (USART1_SR & USART_SR_RXNE) != 0;
}

void
_exit(int c)
{
	while (1)
		;
}
