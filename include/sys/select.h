#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#include <sys/time.h>

typedef long int __fd_mask;

#define __FD_SETSIZE	64

#define __NFDBITS	(8 * (int) sizeof (__fd_mask))
#define	__FD_ELT(d)	((d) / __NFDBITS)
#define	__FD_MASK(d)	((__fd_mask) (1UL << ((d) % __NFDBITS)))
#define __FDS_BITS(set) ((set)->__fds_bits)

typedef struct {
	__fd_mask __fds_bits[__FD_SETSIZE / __NFDBITS];
} fd_set;

#define	FD_SETSIZE	__FD_SETSIZE
#define NFDBITS		__NFDBITS

#define	FD_SET(fd, fdsetp)	__FD_SET (fd, fdsetp)
#define	FD_CLR(fd, fdsetp)	__FD_CLR (fd, fdsetp)
#define	FD_ISSET(fd, fdsetp)	__FD_ISSET (fd, fdsetp)
#define	FD_ZERO(fdsetp)		__FD_ZERO (fdsetp)

extern int select (int __nfds, fd_set *__restrict __readfds,
		   fd_set *__restrict __writefds,
		   fd_set *__restrict __exceptfds,
		   struct timeval *__restrict __timeout);

#endif
