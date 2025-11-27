#include <dos.h>

// dos.h date implementation

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

#define SEC_PER_DAY	86400
#define SEC_PER_HOUR	3600
#define SEC_PER_MIN	60

void
settime(const struct time* ti)
{
#if 0
	struct timeval tv = { .tv_sec = 0, .tv_usec = 0 };

        int ti_hour;    /* 0-23 */
        int ti_min;     /* 0-59 */
        int ti_sec;     /* 0-59 */}

	settimeofday(&tv, NULL);
#endif
}

void
setdate(const struct date* dt)
{
#if 0
	struct timeval tv = { .tv_sec = 0, .tv_usec = 0 };
	settimeofday(&tv, NULL);
#endif
}

void
gettime(struct time* ti)
{
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);

	ti->ti_hour = tm->tm_hour;
	ti->ti_min = tm->tm_min;
	ti->ti_sec = tm->tm_sec;
}

void
getdate(struct date* dt)
{
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);

	dt->da_year = tm->tm_year;
	dt->da_mon = tm->tm_mon;
	dt->da_day = tm->tm_mday;
}
