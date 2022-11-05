#include <stdio.h>

#ifdef LIBIO
extern void _putchar(char c);
extern char _getchar(void);
#else
#include <unistd.h>
#endif

struct _io_buf *_io_table[_NFILES];

struct _io_buf _stdin = { 0, IO_READMODE };
struct _io_buf _stdout = { 0, IO_WRITEMODE };
struct _io_buf _stderr = { 0, IO_WRITEMODE };

int
fgetc(FILE *fp)
{
	char ch;

	if ((fp->_flags & IO_READMODE) == 0)
		return EOF;

#ifdef LIBIO
	ch = _getchar();
#else
	if (read(fp->_fd, &ch, 1) != 1)
		return EOF;
#endif

	return (int)ch;
}

int
fputc(int _c, FILE *fp)
{
	char ch = (char)_c;

	if ((fp->_flags & IO_WRITEMODE) == 0)
		return EOF;

#ifdef LIBIO
	_putchar(ch);
#else
	if (write(fp->_fd, &ch, 1) != 1)
		return EOF;
#endif

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
#ifdef LIBIO
		_putchar(c);
#else
		if (write(fp->_fd, &c, 1) != 1)
			rv = EOF;
#endif
	}
	c = '\n';
#ifdef LIBIO
	_putchar(c);
#else
	if (write(fp->_fd, &c, 1) != 1)
		rv = EOF;
#endif

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
		*cp = (char)c;
	}
	*cp = '\0';

	return s;
}
