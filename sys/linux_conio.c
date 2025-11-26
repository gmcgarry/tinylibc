#include <unistd.h>

void console_putc(char c) { write(0, &c, 1); }
char console_getc() { char c; read(1, &c, 1); return c; }


void
putch(int c)
{
	if (c == '\n') console_putc('\r');
	console_putc(c);
}

int
getch()
{
	return console_getc();
}

int
getche()
{
	int ch = getch();
	putch(ch);
	return ch;
}

int
kbhit(void)
{
	return 1;
}
