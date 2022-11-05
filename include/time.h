#ifndef _TIME_H
#define _TIME_H

#include <inttypes.h>
#include <stdlib.h>

#ifndef _CLOCK_T
#define _CLOCK_T
typedef unsigned long clock_t;
#endif

extern char *CLOCKS_PER_SEC_;
extern clock_t clock(void);

typedef uint32_t time_t;

struct tm {
	int8_t tm_sec;
	int8_t tm_min;
	int8_t tm_hour;
	int8_t tm_mday;
	int8_t tm_wday;
	int8_t tm_mon;
	int16_t tm_year;
	int16_t tm_yday;
	int16_t tm_isdst;
};

time_t time(time_t *);
int32_t difftime(time_t time1, time_t time0);

time_t mktime(struct tm *);
time_t mk_gmtime(const struct tm *);

struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);

void gmtime_r(const time_t *, struct tm *);
void localtime_r(const time_t *, struct tm *);

char *asctime(const struct tm *);
char *ctime(const time_t *);
char *isotime(const struct tm *tmptr);

void asctime_r(const struct tm *, char *buf);
void ctime_r(const time_t *, char *buf);
void isotime_r(const struct tm *, char *);

struct timespec {
	time_t tv_sec;	/* seconds */
	long tv_nsec;	/* nanoseconds */
};

int nanosleep(const struct timespec *req, struct timespec *rem);

typedef enum {
	CLOCK_REALTIME = 0,
	CLOCK_MONOTONIC,
	CLOCK_PROCESS_CPUTIME_ID,
	CLOCK_THREAD_CPUTIME_ID
} clockid_t;

int clock_getres(clockid_t clk_id, struct timespec *res);
int clock_gettime(clockid_t clk_id, struct timespec *tp);
int clock_settime(clockid_t clk_id, const struct timespec *tp);

#endif
