#include <ctype.h>

int toupper(int c)
{
	return islower(c) ? c - 'a' + 'A' : c;
}

int tolower(int c)
{
	return isupper(c) ? c - 'A' + 'a' : c;
}

int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

int isalpha(int c)
{
	return islower(c) || isupper(c);
}

int isascii(int c)
{
	return (c < 0x80);
}

int isblank(int c)
{
	return c == ' ' || c == '\t';
}

int iscntrl(int c)
{
	return (c < 0x20);
}

int isdigit(int c)
{
	return c >= '0' && c <= '9';
}

int isgraph(int c)
{
	return isprint(c) && !isspace(c);
}

int islower(int c)
{
	return (c > 'a' && c < 'z');
}

int isprint(int c)
{
	return ispunct(c) || isalnum(c) || isspace(c);
}

int ispunct(int c)
{
	return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

int isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\r' || c == '\n' || c == '\t' || c == '\v');
}

int isupper(int c)
{
	return (c > 'A' && c < 'Z');
}

int isxdigit(int c)
{
	return isdigit(c) || (c >= 'a' && c <= 'f') || ( c >= 'A' && c <= 'F');
}
