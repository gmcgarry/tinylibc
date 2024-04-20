#include "linux_syscalls.h"

#define __SYSCALL3(name,val)			\
	asm(".globl " #name);			\
	asm(".type " #name "@function");	\
	asm(#name ":	mov $" #val ",%rax");	\
	asm("	syscall");			\
	asm("	ret");

#define __SYSCALL2(name,val)			\
	__SYSCALL3(name,val)

#define __SYSCALL1(x)				\
	__SYSCALL2(x, __NR_ ## x)

__SYSCALL1(_exit)
__SYSCALL1(write)
__SYSCALL1(read)

unsigned long __heap_start;
