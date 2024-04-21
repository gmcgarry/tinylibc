#include <stdio.h>
#include <dos.h>

#include "STM32F100.h"

#define F_LSE	32768	/* LSE oscillator frequency */


static uint8_t rtcok;

int
RTC_init()
{
	__enable_peripheral(BKPEN);					/* Enable BKP and PWR module */
	__enable_peripheral(PWREN);

	PWR_CR |= _BV(8);						/* Enable write access to backup domain */
	RCC_BDCR = 0x00008101;						/* Enable LSE oscillator */

	uint32_t n;
	for (n = 8000000; n && !(RCC_BDCR & _BV(1)); n--)		/* Wait for LSE start and stable */
		;
	if (n) {
		for (n = 100000; n && !(RTC_CRL & _BV(5)); n--)
			;
		if (n) {
			RTC_CRL = _BV(4);				/* Enter RTC configuration mode */
			RTC_PRLH = 0; RTC_PRLL = F_LSE - 1;		/* Set RTC clock divider for 1 sec tick */
			RTC_CRL = 0;					/* Exit RTC configuration mode */
			for ( ; n && !(RTC_CRL & _BV(5)); n--)		/* Wait for RTC internal process */
				;
			for ( ; n && !(RTC_CRL & _BV(3)); n--)		/* Wait for RTC is in sync */
				;
		}
	}

	if (n) {
		rtcok = 1;						/* RTC is available */
	} else {
		rtcok = 0;						/* RTC is not available */
		RCC_BDCR = 0;						/* Stop LSE oscillator */
	}

	PWR_CR &= ~_BV(8);						/* Inhibit write access to backup domain */

	return !rtcok;
}

static int
rtc_setClock(uint32_t tmr)
{
	if (!rtcok)
		return 1;

	uint32_t n = 0;

	PWR_CR |= _BV(8);					/* Enable write access to backup domain */
	for (n = 100000; n && !(RTC_CRL & _BV(5)); n--) ;	/* Wait for end of RTC internal process */
	if (n) {
		RTC_CRL = _BV(4);				/* Enter RTC configuration mode */
		RTC_CNTL = tmr;					/* Set time counter */
		RTC_CNTH = tmr >> 16;
		RTC_PRLL = F_LSE - 1;				/* Set RTC clock divider for 1 sec tick */
		RTC_PRLH = 0;
		RTC_CRL = 0;					/* Exit RTC configuration mode */
		for ( ; n && !(RTC_CRL & _BV(5)); n--)		/* Wait for end of RTC internal process */
			;
	}
	PWR_CR &= ~_BV(8);					/* Inhibit write access to backup domain */

	return 0;
}

int
rtc_getClock(uint32_t* tmr)
{
	if (!rtcok)
		return 1;

	uint32_t t1, t2;
	t1 = RTC_CNTH << 16 | RTC_CNTL;				/* Read RTC counter */
	do {
		t2 = t1;
		t1 = RTC_CNTH << 16 | RTC_CNTL;	
	} while (t1 != t2);
	*tmr = t1;

	return 0;
}

static const uint8_t mdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

void
settime(const struct time* ti)
{
	uint32_t clock = 0;
	rtc_getClock(&clock);

	clock /= 86400;
	clock *= 86400;
	clock += ti->ti_hour * 3600 + ti->ti_min * 60 + ti->ti_sec;

	rtc_setClock(clock);
}

void
setdate(const struct date* da)
{
	uint32_t y = da->da_year - 1970;
	if (y > 2106 || !da->da_mon || !da->da_day)
		return;

	uint32_t oclock = 0;
	rtc_getClock(&oclock);

	uint32_t clock = y / 4 * 1461;
	y %= 4;
	clock += y * 365 + (y > 2 ? 1 : 0);

	for (uint32_t i = 0; i < 12 && i + 1 < da->da_mon; i++) {
		clock += mdays[i];
		if (i == 1 && y == 2)
			clock++;
	}
	clock += da->da_day - 1;
	clock *= 86400;
	clock += (oclock % 86400);

	rtc_setClock(clock);
}

void
gettime(struct time* ti)
{
	uint32_t clock = 0;
	rtc_getClock(&clock);

	ti->ti_sec = (uint8_t)(clock % 60);
	clock /= 60;
	ti->ti_min = (uint8_t)(clock % 60);
	clock /= 60;
	ti->ti_hour = (uint8_t)(clock % 24);
}

void
getdate(struct date* da)
{
	uint32_t clock = 0;
	rtc_getClock(&clock);

	clock /= 60;
	clock /= 60;
	clock /= 24;
	da->da_year = (uint16_t)(1970 + clock / 1461 * 4);
	clock %= 1461;
	uint32_t n = ((clock >= 1096) ? clock - 1 : clock) / 365;
	da->da_year += n;
	clock -= n * 365 + (n > 2 ? 1 : 0);

	uint32_t i;
	for (i = 0; i < 12; i++) {
		uint32_t d = mdays[i];
		if (i == 1 && n == 2) d++;
		if (clock < d) break;
		clock -= d;
	}
	da->da_mon = (uint8_t)(1 + i);
	da->da_day = (uint8_t)(1 + clock);
}
