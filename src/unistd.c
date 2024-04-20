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
