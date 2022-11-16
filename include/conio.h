#ifndef _CONIO_H
#define _CONIO_H

void clrscr();			/* Clears the screen */

int kbhit();			/* Determines if a keyboard key was pressed as well */
void putch(int ch);		/* Writes a character directly to the console */
int getch();			/* Get char entry from the console */
int getche();
void ungetch(int ch);

#define cscanf	scanf		/* Reads formatted values directly from the console */
#define cputs	puts		/* Writes a string directly to the console */
#define cprintf	printf		/* Formats values and writes them directly to the console */

#endif
