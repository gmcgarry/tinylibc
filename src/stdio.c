#include <stdio.h>

#include <unistd.h>

struct _io_buf *_io_table[_NFILES];

struct _io_buf _stdout = { 0, IO_WRITEMODE };
struct _io_buf _stdin = { 1, IO_READMODE };
struct _io_buf _stderr = { 2, IO_WRITEMODE };

int
fgetc(FILE *fp)
{
	char ch;

	if ((fp->_flags & IO_READMODE) == 0)
		return EOF;

	if (read(fp->_fd, &ch, 1) != 1)
		return EOF;

	return (int)ch;
}

int
fputc(int _c, FILE *fp)
{
	char ch = (char)_c;

	if ((fp->_flags & IO_WRITEMODE) == 0)
		return EOF;

	if (write(fp->_fd, &ch, 1) != 1)
		return EOF;

	return _c;
}

int
fputs(const char *s, FILE *fp)
{
	char c;
	int rv = 0;

	if ((fp->_flags & IO_WRITEMODE) == 0)
		return EOF;

	while ((c = *s++) != '\0') {
		if (write(fp->_fd, &c, 1) != 1)
			rv = EOF;
	}
	c = '\n';
	if (write(fp->_fd, &c, 1) != 1)
		rv = EOF;

	return rv;
}

char *
fgets(char *s, int n, FILE *fp)
{
	char c, *cp;

	if ((fp->_flags & IO_READMODE) == 0 || n == 0)
		return NULL;

	n--;
	for (c = 0, cp = s; c != '\n' && n > 0; n--, cp++) {
		if ((c = fgetc(fp)) == EOF)
			return NULL;
		*cp = c;
	}
	*cp = '\0';

	return s;
}
