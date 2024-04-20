#include <stdint.h>

#ifdef F_PCLK2
#define CLOCK_HZ	F_PCLK2
#else
#define CLOCK_HZ	8000000U
#endif

extern int SysTick_Config(uint32_t);
extern void USART1_init(uint32_t);


void USART1_putch(char ch);
void test_blink();

void
__libc_init(void)
{
	USART1_init(9600);
	SysTick_Config(CLOCK_HZ/1000);
}
