#include <unistd.h>

char** environ;

/*
int access(const char* pathname, int mode);
int brk(void* ptr);
int close(int d);
int creat(const char* path, mode_t mode);
int dup(int oldfd);
int dup2(int oldfd, int newfd);
int execl(const char *path, const char* arg, ...);
int execve(const char *path, char *const argv[], char *const envp[]);
int fcntl(int fd, int op, ...);
int isatty(int d);
int isatty(int d);
int kill(pid_t old, int sig);
int open(const char* path, int access, ...);
int pause(void);
int pipe(int pipefd[2]);
int raise(int signum);
int unlink(const char* path);
off_t lseek(int fildes, off_t offset, int whence);
pid_t fork(void);
pid_t getpid(void);
unsigned int alarm(unsigned int seconds);
pid_t wait(int* wstatus);
void _exit(int);
void* sbrk(int increment);
*/


ssize_t
read(int fd, void* buffer, size_t count)
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
write(int fd, void* buffer, size_t count)
{
	char *cp = buffer;

	if (fd != 0 || count != 1)
		return -1;

	char c asm("%d0") = *cp;
	asm("jsr PUTC" : : "r" (c));

	return 1;
}
