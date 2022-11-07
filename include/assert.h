#ifndef _ASSERT_H
#define _ASSERT_H

#ifdef NDEBUG
#define assert(x)	/* NDEBUG */
#else
#define assert(x)	do { if (!(x)) { printf("%s: %d: assertion failed " #x, __FILE__, __LINE__); abort(); } } while (0)
#endif

#endif
