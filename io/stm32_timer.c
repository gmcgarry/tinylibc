#include <stdint.h>

#define __I	volatile
#define __IM	volatile
#define __OM	volatile
#define __IO	volatile
#define __IOM	volatile

#define SysTick_LOAD_RELOAD_Msk		(0xFFFFFFUL)    /*!< SysTick LOAD: RELOAD Mask */

typedef struct
{
	__IOM uint32_t CTRL;		/*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
	__IOM uint32_t LOAD;		/*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
	__IOM uint32_t VAL;		/*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
	__IM  uint32_t CALIB;		/*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

#define SCS_BASE	(0xE000E000UL)			/*!< System Control Space Base Address */
#define SysTick_BASE	(SCS_BASE + 0x0010UL)		/*!< SysTick Base Address */
#define SysTick		((SysTick_Type*) SysTick_BASE)	/*!< SysTick configuration struct */

typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

#define SCB_BASE	(SCS_BASE +  0x0D00UL)		/*!< System Control Block Base Address */
#define SCB		((SCB_Type *) SCB_BASE)		/*!< SCB configuration struct */

typedef struct
{
  __IOM uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  __IOM uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[24U];
  __IOM uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  __IOM uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  __IOM uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  __IOM uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  __OM  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

#define NVIC_BASE	(SCS_BASE +  0x0100UL)		/*!< NVIC Base Address */
#define NVIC		((NVIC_Type *) NVIC_BASE)	/*!< NVIC configuration struct */

#include "stm32f103x6.h"

#define SysTick_CTRL_CLKSOURCE_Pos	2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk	(1UL << SysTick_CTRL_CLKSOURCE_Pos)	/*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos	1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk 	(1UL << SysTick_CTRL_TICKINT_Pos)	/*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Msk		(1UL)					/*!< SysTick CTRL: ENABLE Mask */


static void
NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
	 if ((int32_t)(IRQn) < 0)
		SCB->SHP[(((uint32_t)(int32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
	  else
		NVIC->IP[((uint32_t)(int32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
}

int 
SysTick_Config(uint32_t ticks)
{
	if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
		return 1;

	SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
	NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */

	SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	return 0;
}


volatile uint32_t msTicks = 0;

void
SysTick_Handler(void)
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
