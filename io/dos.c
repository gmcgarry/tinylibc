#include <dos.h>

#include <stdint.h>

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
}

void
setdate(const struct date* dt)
{
}

void
gettime(struct time* ti)
{
	struct regs *regs = (void *)0xFFFFD000;

	ti->ti_sec = regs->sec_hi * 10 + regs->sec_lo;
	ti->ti_min = regs->min_hi * 10 + regs->min_lo;
	ti->ti_hour = regs->hour_hi * 10 + regs->hour_lo;
}

void
getdate(struct date* da)
{
	struct regs *regs = (void *)0xFFFFD000;

	da->da_day = regs->day_hi * 10 + regs->day_lo;
	da->da_mon = regs->mon_hi * 10 + regs->mon_lo;
	da->da_year = 2000 + regs->year_hi * 10 + regs->year_lo;
}
