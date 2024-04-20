#include <string.h>
#include <stdio.h>

#include <getopt.h>

int opterr = 1, optind = 1, optopt, optreset;
char *optarg;

#define BADCH   (int)'?'
#define BADARG  (int)':'
#define EMSG    ""

int
getopt(int nargc, char * const nargv[], const char *ostr)
{
	static char *ptr = EMSG;
	const char *oli;

	if (optreset || !*ptr) {
		optreset = 0;
		if (optind >= nargc || *(ptr = nargv[optind]) != '-') {
			ptr = EMSG;
			return -1;
		}
		if (ptr[1] && *++ptr == '-') {
			++optind;
			ptr = EMSG;
			return -1;
		}
	}
	if ((optopt = (int)*ptr++) == (int)':' || !(oli = strchr(ostr, optopt))) {
		if (optopt == (int)'-')
			return -1;
		if (*ptr == '\0')
			++optind;
		if (opterr && *ostr != ':')
			printf("illegal option -- %c\n", optopt);
		return BADCH;
	}
	if (*++oli != ':') {
		optarg = NULL;
		if (*ptr == '\0')
			++optind;
	} else {
		if (*ptr) {
			optarg = ptr;
		} else if (nargc <= ++optind) {
			ptr = EMSG;
			if (*ostr == ':')
				return BADARG;
			if (opterr)
				printf("option requires an argument -- %c\n", optopt);
			return BADCH;
		} else {
			optarg = nargv[optind];
		}
		ptr = EMSG;
		++optind;
	}
	return optopt;
}
