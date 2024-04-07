ARCH=arm
PLATFORM=$(ARCH)-none-eabi
CFLAGS = -mfloat-abi=soft -mthumb -mcpu=cortex-m3
CC = $(PLATFORM)-gcc
AS = $(PLATFORM)-as
INC = -fno-builtin -nostdinc -I./include -I/usr/lib/gcc/arm-none-eabi/12.2.1/include/
CFLAGS += -DLIBIO
MACH=stm32

#ARCH=m68k
#PLATFORM=$(ARCH)-linux-gnu
#CFLAGS = -mcpu=68000 -msoft-float -O

#ARCH=x86_64
#PLATFORM=$(ARCH)-linux-gnu

#ARCH=pdp11
#PLATFORM=$(ARCH)-none

CC ?= $(PLATFORM)-pcc
AS ?= $(PLATFORM)-as

MACH ?= $(ARCH)

ASFLAGS =
CFLAGS += -Wall -O
INC ?= -nostdinc -I./include -I/usr/local/lib/pcc/$(PLATFORM)/1.2.0.DEVEL/include/

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


.PHONY: $(HDRS)

all:	libc.a libio.a

install:	 install_headers install_libs

install_libs:	 libc.a libio.a
	mkdir -p /usr/local/$(PLATFORM)/lib/
	cp libc.a libio.a /usr/local/$(PLATFORM)/lib/

install_headers:
	mkdir -p /usr/local/$(PLATFORM)/include
	cp -r include/* /usr/local/$(PLATFORM)/include

libc.a:	$(OBJS)
	$(AR) crv $@ $^

LIBIO_C_SOURCES = $(wildcard io/$(MACH)_*.c)
LIBIO_ASM_SOURCES = $(wildcard io/$(MACH)_*.s)
LIBIO_OBJECTS = $(LIBIO_C_SOURCES:.c=.o) $(LIBIO_ASM_SOURCES:.s=.o)
libio.a: $(LIBIO_OBJECTS)
	$(AR) crv $@ $^

clean:
	$(RM) -f $(OBJS) $(LIBIO_OBJECTS) libc.a libio.a

.SUFFIXES: .c .h .s .o

.c.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.s.o:
	$(AS) $(ASFLAGS) -c -o $@ $<
