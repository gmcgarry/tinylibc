#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <stdint.h>
#include <sys/types.h>

typedef int sig_atomic_t;

#define SIG_ERR ((sighandler_t) -1)           /* Error return.  */
#define SIG_DFL ((sighandler_t) 0)            /* Default action.  */
#define SIG_IGN ((sighandler_t) 1)            /* Ignore signal.  */

#define SIGINT          2       /* terminal interrupt */
#define SIGQUIT         3       /* terminal quit */
#define SIGABRT         6       /* abort (ANSI) */
#define	SIGFPE		8	/* floating-point exception */
#define SIGILL          11      /* illegal instruction */
#define SIGALRM         14      /* alarm clock */
#define _NSIG           16      /* biggest signal number + 1 */

typedef uint16_t sigset_t;

struct sigaction;

typedef void (*sighandler_t)(int);

extern int sigaction(int, const struct sigaction *, struct sigaction *);
extern int sigprocmask(int, const sigset_t *, sigset_t *);
extern sighandler_t signal(int signum, sighandler_t handler);

extern int raise(int sig);
extern int kill(pid_t pid, int sig);

#endif
