#include <stdio.h>
#include <stdlib.h>

#include <conio.h>

#include "devsw.h"

void *
console_init(const char* path, int access)
{
	return NULL;
}

int
console_deinit(void *arg)
{
	return -1;
}

int
console_fcntl(void *arg, int op, va_list va)
{
	return -1;
}

off_t
console_lseek(void *arg, off_t offset, int whence)
{
	return -1;
}

ssize_t
console_read(void *arg, void* buffer, size_t count)
{
	char *p = (char *)buffer;
	*p = getch();
	return 1;
}

ssize_t
console_write(void *arg, void* buffer, size_t count)
{
	size_t n = count;
	char *p = (char *)buffer;
	while (n--)
		putch(*p++);
	return count;
}

struct handle {
	int active;
	void *arg;
	struct devsw* dev;
};

struct devsw console = {
	.init = console_init,
	.deinit = console_deinit,
	.fcntl = console_fcntl,
	.lseek = console_lseek,
	.read = console_read,
	.write = console_write
};


static struct handle handles[_NFILES] = { 
	{ 1, NULL, &console },
	{ 1, NULL, &console },
	{ 1, NULL, &console }
};

int
open(const char* path, int access, ...)
{
#if 0
	for (int i = 0; i < _NFILES; i++) {
		if (handles[i].active)
			continue;
		// create a new entry in the table of handles
		return handles[fd].dev->init(handles[fd].arg);
	}
#endif
	return -1;
}

int
close(int fd)
{
	return handles[fd].dev->deinit(handles[fd].arg);
}

int
dup(int fd)
{
	return -1;
}

int
fcntl(int fd, int op, ...)
{
	va_list va;
	va_start(va, op);
	int rc = handles[fd].dev->fcntl(handles[fd].arg, op, va);
	va_end(va);
	return rc;
}

off_t
lseek(int fd, off_t offset, int whence)
{
	return handles[fd].dev->lseek(handles[fd].arg, offset,whence);
}

ssize_t
read(int fd, void* buffer, size_t count)
{
	return handles[fd].dev->read(handles[fd].arg, buffer, count);
}

ssize_t
write(int fd, void* buffer, size_t count)
{
	return handles[fd].dev->write(handles[fd].arg, buffer, count);
}
