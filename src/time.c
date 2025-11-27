#include <time.h>

/*
 * time functions implemented over gettimeofday() API.
 * systems need to provide gettimeofday()
 */

#include <sys/types.h>
#include <sys/time.h>

#define SEC_PER_DAY	86400
#define SEC_PER_HOUR	3600
#define SEC_PER_MIN	60


int
nanosleep(const struct timespec *req, struct timespec *rem)
{
	return 0;
}

time_t
time(time_t* timep)
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

        time_t total = tv.tv_sec % SEC_PER_DAY;
        total += tz.tz_dsttime * SEC_PER_HOUR;
        total -= tz.tz_minuteswest * SEC_PER_MIN;
        // mod `hms` to ensure in positive range of [0...SEC_PER_DAY)
        total = (total + SEC_PER_DAY) % SEC_PER_DAY;

	if (timep)
		*timep = total;
	return total;
}

struct tm *
localtime(const time_t *timep)
{
	static struct tm tm;

	tm.tm_sec = *timep % SEC_PER_MIN;
	tm.tm_min = (*timep % SEC_PER_HOUR) / SEC_PER_MIN;
        tm.tm_hour = (*timep % SEC_PER_DAY) / SEC_PER_HOUR;

	tm.tm_mday = 0; // TODO
	tm.tm_wday = 0; // TODO
	tm.tm_mon = 0; // TODO
	tm.tm_year = 0; // TODO
	tm.tm_yday = 0; // TODO
	tm.tm_isdst = 0; // TODO

	return &tm;
}
