#ifndef _DOS_H
#define _DOS_H

struct date {
	int da_day;
	int da_mon;
	int da_year;
};

struct time {
	int ti_hour;
	int ti_min;
	int ti_sec;
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
