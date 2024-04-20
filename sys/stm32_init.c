#include <stdint.h>

extern int SysTick_Config(uint32_t);
extern void USART1_init(uint32_t);

#define CLOCK_HZ	8000000U

void
__libc_init(void)
{
	USART1_init(9600);
	SysTick_Config(CLOCK_HZ/1000);
}
