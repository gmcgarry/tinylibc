#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>

#define BUFSIZ		1024
#define _NBF		8
#define _BUFSIZ		(_NBF * BUFSIZ)
#define _NFILES		20
#define EOF		(-1)

#define IO_READMODE	1
#define IO_WRITEMODE	2
#define IO_UNBUFF	4
#define IO_EOF		8
#define IO_ERR		16
#define IO_MYBUF	32
#define IO_PERPRINTF	64

#ifndef FILE
extern struct _io_buf {
	int _fd;
	int _flags;
} *_io_table[_NFILES], _stdin, _stdout, _stderr;
#define FILE struct _io_buf
#endif	/* FILE */

#define stdin		(&_stdin)
#define stdout		(&_stdout)
#define stderr		(&_stderr)

#define STDIN_FILENO	fileno(stdin)

#define fileno(p) 	((p)->_fd)
#define feof(p) 	(((p)->_flags & IO_EOF) != 0)
#define ferror(p) 	(((p)->_flags & IO_ERR) != 0)
#define getchar() 	getc(stdin)
#define putchar(c) 	putc(c,stdout)
#define getc(p)		fgetc(p)
#define putc(c, p)	fputc(c, p)
#define puts(s)		fputs(s,stdout)

extern int fgetc(FILE *);
extern int fputc(int, FILE *);

extern char *fgets(char *, int, FILE *);
extern int fputs(const char *, FILE *);

typedef long int fpos_t;

extern void setbuf(FILE *stream, char *buf);
extern void rewind(FILE *);
extern long ftell(FILE *);

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

extern int fseek(FILE *, long *, int);
extern int fflush(FILE *);

extern FILE *fopen(const char *, const char *);
extern int fclose(FILE *);

int printf(const char* format, ...);
int sprintf(char *str, const char *format, ...);

#endif
