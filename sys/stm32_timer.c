#include <stdint.h>

#include "STM32F100.h"

#define RVR_RELOAD_Msk		(0xFFFFFFUL)			/*!< SysTick RVR: RELOAD Mask */

#define CSR_CLKSOURCE_Pos	2U				/*!< SysTick CSR: CLKSOURCE Position */
#define CSR_CLKSOURCE_Msk	(1UL << CSR_CLKSOURCE_Pos)	/*!< SysTick CSR: CLKSOURCE Mask */

#define CSR_TICKINT_Pos	1U					/*!< SysTick CSR: TICKINT Position */
#define CSR_TICKINT_Msk 	(1UL << CSR_TICKINT_Pos)	/*!< SysTick CSR: TICKINT Mask */

#define CSR_ENABLE_Msk		(1UL)				/*!< SysTick CSR: ENABLE Mask */

int 
SysTick_Config(uint32_t ticks)
{
	if ((ticks - 1UL) > RVR_RELOAD_Msk)
		return 1;

	SYST_RVR = (uint32_t)(ticks - 1UL);			/* set reload register */
#if 0
	__set_faultn_priority(SysTick_IRQn, 1);			/* set Priority for Systick Interrupt */
#endif
	SYST_CVR = 0UL;						/* Load the SysTick Counter Value */
	SYST_CSR = CSR_CLKSOURCE_Msk | CSR_TICKINT_Msk | CSR_ENABLE_Msk;

	return 0;
}

volatile uint32_t msTicks = 0;

void
__libc_systick(void)
{
	msTicks++;
}

void
delay(unsigned int ms)
{
	uint32_t expected_ticks = msTicks + ms;
	while (msTicks < expected_ticks)
		__asm("nop");
}
