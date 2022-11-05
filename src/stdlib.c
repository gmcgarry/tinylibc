#include <stdlib.h>
#include <unistd.h>	// for _exit()

extern __malloc_cleanup();

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
