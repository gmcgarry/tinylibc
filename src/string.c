#include "string.h"

void *
memcpy(void *_s1, const void *_s2, size_t _n)
{
	unsigned char *s1 = _s1;
	const unsigned char *s2 = _s2;

	while (_n-- > 0)
		*s1++ = *s2++;

	return _s1;
}

void *
memmove(void *_s1, const void *_s2, size_t _n)
{
	unsigned char *s1 = _s1;
	const unsigned char *s2 = _s2;

	if (_s1 < _s2) {
		while (_n-- > 0)
			*s1++ = *s2++;
	} else {
		s1 += _n;
		s2 += _n;
		while (_n-- > 0)
			*--s1 = *--s2;
	}

	return _s1;
}

void *
memset(void *_s, int _c, size_t _n)
{
	unsigned char *p = _s;
	while (_n--)
		*p++ = _c;
	return _s;
}

void *
memchr(const void *s, int c, size_t n)
{
	unsigned char *p = (unsigned char *)s;
	unsigned char *end = p + n;
	for (; p != end; p++)
		if (*p == (unsigned char)c)
			return p;
	return 0;
}

int
memcmp(const void *_s1, const void *_s2, size_t n)
{
	const unsigned char *s1 = _s1;
	const unsigned char *s2 = _s2;

	unsigned  char c1, c2;
	while ((c1 = *s1++) == (c2 = *s2++) && n--)
		;
	if (c1 != c2)
		return c1 < c2 ? -1 : 1;
	return 0;
}

int
strcmp(const char *s1, const char *s2)
{
	char c1, c2;
	while ((c1 = *s1++) == (c2 = *s2++)) {
		if (c1 == 0 || c2 == 0)
			break;
	}
	if (c1 == 0 && c2 == 0)
		return 0;
	if (c1 == 0)
		return -1;
	return 1;
}

size_t
strlen(const char *s)
{
	size_t cnt = 0;
	while (*s++)
		cnt++;
	return cnt;
}

char *
stpcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (void *)src;
}

char *
strcpy(char *dst, const char *src)
{
	stpcpy(dst, src);
	return dst;
}

char *
strcat(char *dst, const char *src)
{
	stpcpy(dst + strlen(dst), src);
	return dst;
}

char *
strchr(const char *s, int c)
{
	char *p = (char *)(void *)s;
	for (; *p; p++)
		if (*p == (char)c)
			return p;
	return NULL;
}


