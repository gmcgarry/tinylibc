#include <stdio.h>
#include <stdint.h>

#ifdef F_PCLK2
#define CLOCK_HZ	F_PCLK2
#else
#define CLOCK_HZ	8000000U
#endif

extern int SYSTICK_init(uint32_t);
extern int RTC_init();
extern void USART1_init(uint32_t);

void test_blink();

void
__libc_init(void)
{
	USART1_init(9600);
	int rc = SYSTICK_init(CLOCK_HZ/1000);
	if (rc)
		printf("system timer not available\n");
	rc = RTC_init();
	if (rc)
		printf("RTC not available\n");
}
