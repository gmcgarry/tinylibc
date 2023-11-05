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

ssize_t
read(int fd, void *buffer, size_t count)
{
	char *cp = buffer;

	if (fd != 0 || count != 1)
		return -1;

	char c asm("%d0");
	asm("jsr GETC" : "=r" (c));
	*cp = c;

	return 1;
}

ssize_t
write(int fd, void *buffer, size_t count)
{
	char *cp = buffer;

	if (fd != 0 || count != 1)
		return -1;

	char c asm("%d0") = *cp;
	asm("jsr PUTC" : : "r" (c));

	return 1;
}
