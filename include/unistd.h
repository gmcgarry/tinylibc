#ifndef _UNISTD_H
#define _UNISTD_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

enum
{
    O_ACCMODE = 0x3,
        
    O_RDONLY = 0,
    O_WRONLY = 1,
    O_RDWR = 2,
        
    O_TEXT = 010000,
    O_BINARY = 020000,
    O_CREAT = 0100,
    O_TRUNC = 01000,
    O_APPEND = 02000,
    O_NONBLOCK = 04000
};

extern char** environ;

extern int access(const char* pathname, int mode);
extern int brk(void* ptr);
extern int close(int d);
extern int creat(const char* path, mode_t mode);
extern int dup(int oldfd);
extern int dup2(int oldfd, int newfd);
extern int execl(const char *path, const char* arg, ...);
extern int execve(const char *path, char *const argv[], char *const envp[]);
extern int fcntl(int fd, int op, ...);
extern int isatty(int d);
extern int isatty(int d);
extern int kill(pid_t old, int sig);
extern int open(const char* path, int access, ...);
extern int pause(void);
extern int pipe(int pipefd[2]);
extern int raise(int signum);
extern int unlink(const char* path);
extern off_t lseek(int fildes, off_t offset, int whence);
extern pid_t fork(void);
extern pid_t getpid(void);
extern unsigned int alarm(unsigned int seconds);
extern pid_t wait(int* wstatus);
extern ssize_t read(int fd, void* buffer, size_t count);
extern ssize_t write(int fd, void* buffer, size_t count);
extern void _exit(int);
extern void* sbrk(int increment);

#endif
