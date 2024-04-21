#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#define min(_a,_b) ((_a) < (_b) ? (_a) : (_b))

enum flag_itoa {
	FILL_ZERO = 1,
	PUT_PLUS = 2,
	PUT_MINUS = 4,
	BASE_2 = 8,
	BASE_8 = 16,
	BASE_10 = 32,
};

static char *
sitoa(char *buf, unsigned int num, int width, enum flag_itoa flags)
{
	unsigned int base;
	char tmp[32];
	char *p = tmp;
	char fill;

	if (flags & BASE_2)
		base = 2;
	else if (flags & BASE_8)
		base = 8;
	else if (flags & BASE_10)
		base = 10;
	else
		base = 16;

	do {
		int rem = num % base;
		*p++ = (rem <= 9) ? (rem + '0') : (rem + 'a' - 0xA);
	} while ((num /= base));
	width -= p - tmp;
	fill = (flags & FILL_ZERO)? '0' : ' ';
	while (0 <= --width) {
		*(buf++) = fill;
	}
	if (flags & PUT_MINUS)
		*(buf++) = '-';
	else if (flags & PUT_PLUS)
		*(buf++) = '+';
	do
		*(buf++) = *(--p);
	while (tmp < p)
		;
	return buf;
}

int
vsprintf(char * buf, const char * fmt, va_list va)
{
	char c;
	const char *save = buf;

	while ((c  = *fmt++)) {
		int width = 0;
		enum flag_itoa flags = 0;
		if (c != '%') {
			*(buf++) = c;
			continue;
		}
redo_spec:
		c  = *fmt++;
		switch (c) {
		case '%':
			*(buf++) = c;
			break;
		case 'c':
			*(buf++) = (char)va_arg(va, int);
			break;
		case 'd':
			{
			int num = (int)va_arg(va, int);
			if (num < 0) {
				num = -num;
				flags |= PUT_MINUS;
			}
			buf = sitoa(buf, num, width, flags | BASE_10);
			}
			break;
		case 'a':
			{
			union { double d; struct { unsigned int h; unsigned int l; } u; } flt;
			flt.d = (double)va_arg(va, double);
			buf = sitoa(buf, flt.u.h, 8, flags | FILL_ZERO);
			buf = sitoa(buf, flt.u.l, 8, flags | FILL_ZERO);
			}
			break;
		case 'u':
			buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_10);
			break;
		case 'o':
			buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_8);
			break;
		case 'X':
		case 'x':
			buf = sitoa(buf, va_arg(va, unsigned int), width, flags);
			break;
		case 'b':
			buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_2);
			break;
		case 's':
			{
			const char *p  = va_arg(va, const char *);
			if (p) {
				while (*p)
					*(buf++) = *(p++);
			}
			}
			break;
		case 'm':
			{
			const uint8_t *m  = va_arg(va, const uint8_t *);
			width = min(width, 64); // buffer limited to 256!
			if (m) {
				for (;;) {
					buf = sitoa(buf, *(m++), 2, FILL_ZERO);
					if (--width <= 0)
						break;
					*(buf++) = ':';
				}
			}
			}
			break;
		case '0':
			if (!width)
				flags |= FILL_ZERO;
			// fall through
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			width = width * 10 + c - '0';
			goto redo_spec;
		case '*':
			width = va_arg(va, unsigned int);
			goto redo_spec;
		case '+':
			flags |= PUT_PLUS;
			goto redo_spec;
		case '\0':
		default:
			*(buf++) = '?';
		}
		width = 0;
	}
	*buf = '\0';
	return buf - save;
}

int
sprintf(char * buf, const char * fmt, ...)
{
	int ret;
	va_list va;
	va_start(va,fmt);
	ret = vsprintf(buf, fmt, va);
	va_end(va);
	return ret;
}

int
printf(const char * fmt, ...)
{
	char buf[256], *p;
	int ret;
	va_list va;
	va_start(va,fmt);
	ret = vsprintf(buf, fmt, va);
	va_end(va);
	p = buf;
	while (*p)
		putchar(*p++);
	return ret;
}


#if TEST
int
main(int argc, char *argv[])
{
	printf("%x %d %b\n", 123, 123, 123);
	return 0;
}
#endif
