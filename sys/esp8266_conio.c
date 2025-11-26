#include "esp8266_rom.h"

void
putch(int c)
{
	if (c == '\n') ets_putc('\r');
	ets_putc(c);
}

int
getch()
{
	char ch;
	ets_getc(&ch);
	return ch;
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

void
delay(unsigned int ms)
{
	ets_delay_us(ms * 1000);
}

void
_exit(int c)
{
	while (1)
		;
}
