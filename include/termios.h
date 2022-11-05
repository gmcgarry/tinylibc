#ifndef _TERMIOS_H
#define _TERMIOS_H

/* c_cflag bit meaning */
#define  B0	0000000		/* hang up */
#define  B50	0000001
#define  B75	0000002
#define  B110	0000003
#define  B134	0000004
#define  B150	0000005
#define  B200	0000006
#define  B300	0000007
#define  B600	0000010
#define  B1200	0000011
#define  B1800	0000012
#define  B2400	0000013
#define  B4800	0000014
#define  B9600	0000015
#define  B19200	0000016
#define  B38400	0000017

/* c_lflag bits */
#define ISIG	0000001   /* Enable signals.  */
#define ICANON	0000002   /* Canonical input (erase and kill processing).  */
#define XCASE	0000004
#define ECHO	0000010   /* Enable echo.  */
#define ECHOE	0000020   /* Echo erase character as error-correcting backspace.  */
#define ECHOK	0000040   /* Echo KILL.  */
#define ECHONL	0000100   /* Echo NL.  */
#define NOFLSH	0000200   /* Disable flush after interrupt or quit.  */
#define TOSTOP	0000400   /* Send SIGTTOU for background output.  */
#define IEXTEN	0100000   /* Enable implementation-defined input processing.  */

/* tcsetattr uses these.  */
#define	TCSANOW		0
#define	TCSADRAIN	1
#define	TCSAFLUSH	2

/* tcflow() and TCXONC use these */
#define	TCOOFF		0
#define	TCOON		1
#define	TCIOFF		2
#define	TCION		3

/* tcflush() and TCFLSH use these */
#define	TCIFLUSH	0
#define	TCOFLUSH	1
#define	TCIOFLUSH	2

typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

#define NCCS 32
struct termios {
	tcflag_t c_iflag;	/* input mode flags */
	tcflag_t c_oflag;	/* output mode flags */
	tcflag_t c_cflag;	/* control mode flags */
	tcflag_t c_lflag;	/* local mode flags */
    	cc_t c_line;		/* line discipline */
	cc_t c_cc[NCCS];	/* control characters */
	speed_t c_ispeed;	/* input speed */
	speed_t c_ospeed;	/* output speed */
};

extern speed_t cfgetospeed(const struct termios *__termios_p);
extern speed_t cfgetispeed(const struct termios *__termios_p);
extern int cfsetospeed(struct termios *__termios_p, speed_t __speed);
extern int cfsetispeed(struct termios *__termios_p, speed_t __speed);
extern int cfsetspeed(struct termios *__termios_p, speed_t __speed);
extern int tcgetattr(int __fd, struct termios *__termios_p);
extern int tcsetattr(int __fd, int __optional_actions, const struct termios *__termios_p);
extern void cfmakeraw(struct termios *__termios_p);
extern int tcsendbreak(int __fd, int __duration);
extern int tcdrain(int __fd);
extern int tcflush(int __fd, int __queue_selector);
extern int tcflow(int __fd, int __action);

#endif
