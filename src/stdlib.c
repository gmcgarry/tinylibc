#include <stdlib.h>
#include <unistd.h>	// for _exit()

extern void __malloc_cleanup();

struct _atexit {
	struct _atexit *next;
	void (*func)(void);
};

static struct _atexit *_atexit_list;
	
int
atexit(void (*_func)(void))
{
	struct _atexit *p = malloc(sizeof(struct _atexit));
	if (!p)
		return 1;
	p->next = _atexit_list;
	p->func = _func;
	_atexit_list = p;

	return 0;
}

void
exit(int _status)
{
	struct _atexit **p = &_atexit_list;

	while (*p) {
		struct _atexit *p2 = *p;
		p2->func();
		*p = p2->next;
		free(p2);
	}

	__malloc_cleanup();

	_exit(_status);
}

void
_Exit(int _status)
{
	_exit(_status);
}

void
abort(void)
{
	_exit(1);
}

static unsigned long next = 1;

void
srand(unsigned int seed)
{
	next = seed;
}

int
rand(void)
{
 	next = next * 1103515245;
	next += 12345;
	return (next % (RAND_MAX + 1));
}

int
abs(int j)
{
	return(j < 0 ? -j : j);
}

long
labs(long j)
{
	return(j < 0 ? -j : j);
}

const void *
bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*_compar)(const void *, const void *))
{
	for (const char *left = base; nmemb; ) {
		const char *middle = left + nmemb / 2 * size;
		int c = (*_compar)(key, middle);
		if (c < 0) {
			nmemb = nmemb / 2;
		} else if (c > 0) {
			left = middle + size;
			nmemb = (nmemb - 1) / 2;
		} else {
			return middle;
		}
	}

	return 0;
}

#include <ctype.h>

long
strtol(const char *nptr, char **endptr, int base)
{
	while (*nptr && isspace(*nptr))
		nptr++;

	int positive = 1;
	if (*nptr == '-')
		positive = 0;
	if (*nptr == '-' || *nptr == '+')
		nptr++;

	long value = 0;
	while (isdigit(*nptr)) {
		value = (value * base) - (*nptr - '0');
		nptr++;
	}
	if (positive)
		value = -value;

	if (endptr)
		*endptr = (void *)nptr;

	return value;
}
