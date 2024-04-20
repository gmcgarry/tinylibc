#ifndef _GETOPT_H
#define _GETOPT_H

extern int opterr, optind, optopt, optreset;
extern char *optarg;

int getopt(int nargc, char * const nargv[], const char *ostr);

#endif
