#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <stddef.h>

#ifndef _TIME_T
#define _TIME_T
typedef unsigned long   time_t;
#endif  /* TIME_T */

#ifndef _CLOCK_T
#define _CLOCK_T
typedef unsigned long	clock_t;
#endif

#ifndef _POSIX_SOURCE

/* major part of a device */
#define	major(x)	((int)(((unsigned)(x)>>8)&0377))

/* minor part of a device */
#define	minor(x)	((int)((x)&0377))

/* make a device number */
#define	makedev(x,y)	((dev_t)(((x)<<8) | (y)))

typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;

typedef	struct	_physadr { int r[1]; } *physadr;
typedef	long	daddr_t;
typedef	char *	caddr_t;
typedef	u_short ino_t;
typedef	long	swblk_t;

typedef int	pid_t;
typedef unsigned short	gid_t;
typedef unsigned short	uid_t;
typedef unsigned int	speed_t;
typedef unsigned long	tcflag_t;
typedef unsigned char	cc_t;
typedef unsigned short  mode_t; /* mode number within an i-node */

typedef	long	label_t[14];
typedef	short	dev_t;
typedef	long	off_t;

/* system V compatibility: */
typedef unsigned int	uint;
typedef unsigned short	ushort;
typedef unsigned char	uchar_t;
typedef short		cnt_t;
typedef long		paddr_t;
typedef long		key_t;

typedef long long		quad_t;
typedef unsigned long long	u_quad_t;

#endif  /* _POSIX_SOURCE */

#endif
