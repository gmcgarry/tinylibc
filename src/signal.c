#include <sys/types.h>
#include <signal.h>

#include <stdlib.h>	// for abort()
#include <unistd.h>	// for getpid()

int
raise(int sig)
{
	return kill(getpid(), sig);
}

int
kill(pid_t pid, int sig)
{
	abort();
	return 0;
}
