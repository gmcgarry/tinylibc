#include <stdint.h>
#include <stdarg.h>

#include <sys/types.h>

struct devsw
{
	void *(*init)(const char* path, int access);
	int (*deinit)(void *arg);
	int (*fcntl)(void *arg, int op, va_list va);
	off_t (*lseek)(void *arg, off_t offset, int whence);
	ssize_t (*read)(void *arg, void* buffer, size_t count);
	ssize_t (*write)(void *arg, void* buffer, size_t count);
};
