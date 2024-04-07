/* stubs if not provided by OS-specific syscalls */

#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

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

#ifdef M68K
	char c asm("%d0");
	asm("jsr GETC" : "=r" (c));
#else
	char c = getchar();
#endif
	*cp = c;

	return 1;
}

ssize_t
write(int fd, void *buffer, size_t count)
{
	char *cp = buffer;

	if (fd != 0 || count != 1)
		return -1;

#ifdef M68K
	char c asm("%d0") = *cp;
	asm("jsr PUTC" : : "r" (c));
#else
	char c = *cp;
	putchar(c);
#endif
	return 1;
}
