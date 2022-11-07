#ifndef _DOS_H_
#define _DOS_H_

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

#endif
