#ifndef _SYS_TIME_H
#define _SYS_TIME_H

struct timeval
{
        time_t tv_sec;
        time_t tv_usec;
};

struct timezone
{
        int tz_minuteswest;
        int tz_dsttime;
};

extern int settimeofday(const struct timeval* tv, const struct timezone* tz);
extern int gettimeofday(struct timeval* tv, struct timezone* tz);

#endif
