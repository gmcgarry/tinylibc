#ifndef _DOS_H
#define _DOS_H

struct date {
	int da_day;	/* 1-31 */
	int da_mon;	/* 1-12 */
	int da_year;	/* 0-2106 */
};

struct time {
	int ti_hour;	/* 0-23 */
	int ti_min;	/* 0-59 */
	int ti_sec;	/* 0-59 */
};

void settime(const struct time* ti);
void setdate(const struct date* dt);

void gettime(struct time* ti);
void getdate(struct date* dt);

void delay(unsigned int ms);
void sleep(unsigned int seconds);

void sound(unsigned int freq);
void nosound(void);

#endif
