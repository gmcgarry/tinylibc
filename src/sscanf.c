#include <ctype.h>
#include <stdarg.h>

int
sscanf(const char *str, const char *format, ...)
{
	const char *start = str;
	va_list args;
	
	va_start(args, format);
	for ( ; *format != '\0'; format++) {
		if (format[0] == '%' && format[1] == 'd') {
			int positive = 1;
			if (*str == '-') {
				positive = 0;
				str++;
			}
			if (!isdigit(*str))
				break;
			int value = 0;
			do {
				value = (value * 10) - (*str - '0');
				str++;
			} while (isdigit(*str));
			if (positive)
				value = -value;
			int *valp = va_arg(args, int *);
			*valp = value;
			format++;
		} else if (*format == *str) {
			str++;
		} else
			break;
	}
	va_end(args);
	return str - start;
}
