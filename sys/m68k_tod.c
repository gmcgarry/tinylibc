#include <dos.h>

#include <stdint.h>

// dos.h date implementation using MSM6242B RTC.

struct regs {
	uint8_t sec_lo;
	uint8_t sec_hi;
	uint8_t min_lo;
	uint8_t min_hi;
	uint8_t hour_lo;
	uint8_t hour_hi;
	uint8_t day_lo;
	uint8_t day_hi;
	uint8_t mon_lo;
	uint8_t mon_hi;
	uint8_t year_lo;
	uint8_t year_hi;
	uint8_t week;
	uint8_t ctl_d;
	uint8_t ctl_e;
	uint8_t ctl_f;
};

void
settime(const struct time* ti)
{
	struct regs *regs = (void *)0xFFFFD000;

	regs->ctl_d = 0;
	regs->ctl_e = 1;	// disable STD.P
	regs->ctl_f = 4;

	regs->sec_lo = ti->ti_sec % 10;
	regs->sec_hi = ti->ti_sec / 10;

	regs->min_lo = ti->ti_min % 10;
	regs->min_hi = ti->ti_min / 10;

	regs->hour_lo = ti->ti_hour % 10;
	regs->hour_hi = ti->ti_hour / 10;
}

void
setdate(const struct date* dt)
{
	struct regs *regs = (void *)0xFFFFD000;

	int year = dt->da_year - 1970;

	regs->ctl_d = 0;
	regs->ctl_e = 1;	// disable STD.P
	regs->ctl_f = 4;

	regs->day_lo = dt->da_day % 10;
	regs->day_hi = dt->da_day / 10;

	regs->mon_lo = dt->da_mon % 10;
	regs->mon_hi = dt->da_mon / 10;

	regs->year_lo = year % 10;
	regs->year_hi = year / 10;
}

void
gettime(struct time* ti)
{
	struct regs *regs = (void *)0xFFFFD000;

	ti->ti_sec = (regs->sec_hi & 0xF) * 10 + (regs->sec_lo & 0xF);
	ti->ti_min = (regs->min_hi & 0xF) * 10 + (regs->min_lo & 0xF);
	ti->ti_hour = (regs->hour_hi & 0xF) * 10 + (regs->hour_lo & 0xF);
}

void
getdate(struct date* dt)
{
	struct regs *regs = (void *)0xFFFFD000;

	dt->da_day = (regs->day_hi & 0xF) * 10 + (regs->day_lo & 0xF);
	dt->da_mon = (regs->mon_hi & 0xF) * 10 + (regs->mon_lo & 0xF);
	dt->da_year = 1970 + (regs->year_hi & 0xF) * 10 + (regs->year_lo & 0xF);
}
