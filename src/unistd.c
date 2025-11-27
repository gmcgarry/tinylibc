/* stubs if not provided by OS-specific syscalls */

#include <sys/types.h>
#include <unistd.h>

char** environ;

pid_t
getpid(void)
{
	return 0;
}

pid_t
getppid(void)
{
	return 0;
}

extern void *__heap_start;
extern void *__heap_end;

static void *heaptop = &__heap_start;

int
brk(void *addr)
{
	heaptop = addr;
	return 0;
}	       
		
void *  
sbrk(intptr_t increment)
{       
	void *last = heaptop;
	heaptop += increment;
	return last;
}       

