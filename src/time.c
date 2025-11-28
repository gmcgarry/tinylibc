#include <stdio.h>	// sprintf
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

static const char *WeekDays[7] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static const char *Months[12] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const uint8_t MonthDays[] = {
	31,28,31,30,31,30,31,31,30,31,30,31
};

static int 
weekday(int mday, int month, int year)
{
	mday += 1;
	month += 1;

	if (month <= 2) {
		year--;
		month += 12;
	}

	month -= 2;
	return (mday + year + year / 4 - year / 100 + year / 400 + (31 * month) / 12) % 7;
}

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

        time_t total = tv.tv_sec;
        total += tz.tz_dsttime * SEC_PER_HOUR;
        total -= tz.tz_minuteswest * SEC_PER_MIN;

	if (timep)
		*timep = total;
	return total;
}

struct tm *
localtime(const time_t *timep)
{
	static struct tm tm;
	time_t t = *timep;

	tm.tm_sec = t % SEC_PER_MIN;
	tm.tm_min = (t % SEC_PER_HOUR) / SEC_PER_MIN;
        tm.tm_hour = (t % SEC_PER_DAY) / SEC_PER_HOUR;

	t /= SEC_PER_DAY;
        tm.tm_year = (uint16_t)(1970 - 1900 + t / 1461 * 4);
        t %= 1461;
        unsigned int n = ((t >= 1096) ? t - 1 : t) / 365;
        tm.tm_year += n;
        t -= n * 365 + (n > 2 ? 1 : 0);

	tm.tm_yday = t % 365;;

        unsigned int i;
        for (i = 0; i < 12; i++) {
                uint32_t d = MonthDays[i];
                if (i == 1 && n == 2) d++;
                if (t < d) break;
                t -= d;
        }
        tm.tm_mon = i;
        tm.tm_mday = 1+t;
	tm.tm_wday = weekday(t, i, tm.tm_year);

	tm.tm_isdst = 0; // TODO

	return &tm;
}

void
asctime_r(const struct tm *tp, char *buf)
{
//	sprintf(buf, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n", WeekDays[tp->tm_wday], Months[tp->tm_mon], tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec, 1900 + tp->tm_year);
	sprintf(buf, "%s %s %d %02d:%02d:%02d %d\n", WeekDays[tp->tm_wday], Months[tp->tm_mon], tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec, 1900 + tp->tm_year);
}

char *
asctime(const struct tm *tp)
{
	static char buf[64];
	asctime_r(tp, buf);
	return buf;
}
