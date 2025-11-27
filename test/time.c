#include <stdio.h>
#include <time.h>

int
main(int argc, char *argv[])
{

	time_t t = time(NULL);
	struct tm* tm = localtime(& t);

	printf("The time is: %s\n", asctime(tm));

	return 0;
}
