CC=m68k-linux-gnu-pcc
AS=m68k-linux-gnu-as

ASFLAGS=
CFLAGS = -Wall -DLIBIO -mcpu=68000 -msoft-float -O
SRCS = \
	src/ctype.c \
	src/printf.c \
	src/sscanf.c \
	src/stdio.c \
	src/stdlib.c \
	src/malloc.c \
	src/string.c \
	src/signal.c \
	src/time.c \
	src/unistd.c
HDRS = $(wildcard include/*.h include/sys/*.h include /machine/*.h)
OBJS = $(SRCS:.c=.o)

INC=-nostdinc -I./include -I/usr/local/lib/pcc/m68k-unknown-linux-gnu/1.2.0.DEVEL/include/

.PHONY: $(HDRS)

all:	libc.a libio.a

install:	 libc.a libio.a
	cp libc.a libio.a /usr/local/m68k-linux-gnu/lib/

libc.a:	$(OBJS)
	$(AR) crv $@ $^

libio.a: io/m68k_acia.o io/m68k_timer.o io/dos.o
	$(AR) crv $@ $^

clean:
	$(RM) -f $(OBJS) libc.a libio.a

.SUFFIXES: .c .h .s .o

.c.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.s.o:
	$(AS) $(ASFLAGS) -c -o $@ $<
