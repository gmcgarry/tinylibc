CC=m68k-linux-gnu-pcc
AS=m68k-linux-gnu-as

ASFLAGS=
CFLAGS = -Wall -DLIBIO -mcpu=68000 -msoft-float -O
SRCS = \
	src/ctype.c \
	src/printf.c \
	src/stdio.c \
	src/stdlib.c \
	src/malloc.c \
	src/string.c \
	src/signal.c \
	src/time.c \
	src/unistd.c
OBJS = $(SRCS:.c=.o)

INC=-nostdinc -I./include -I/usr/local/lib/pcc/m68k-unknown-linux-gnu/1.2.0.DEVEL/include/

all:	libc.a libio.a

install:	libc.a libio.a
	cp libc.a libio.a /usr/local/m68k-linux-gnu/lib/

libc.a:	$(OBJS)
	$(AR) crv $@ $^

#libio.a: io/m68k.o
libio.a: io/m68k_acia.o
	$(AR) crv $@ $^

clean:
	$(RM) -f $(OBJS) libc.a libio.a

.SUFFIXES: .c .s .o

.c.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.s.o:
	$(AS) $(ASFLAGS) -c -o $@ $<
