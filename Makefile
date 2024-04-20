#TARGET := 'linux'
#TARGET := 'stm32'
TARGET := 'esp8266'

ifeq ($(TARGET), 'stm32')
	ARCH=arm
	PLATFORM=$(ARCH)-none-eabi
	CC = $(PLATFORM)-gcc
	CFLAGS = -mfloat-abi=soft -mthumb -mcpu=cortex-m3 -fno-builtin
	AS = $(PLATFORM)-as
	INC = -I/usr/lib/gcc/arm-none-eabi/12.2.1/include/
	CFLAGS += -DLIBIO
	MACH=stm32
endif

ifeq ($(TARGET), 'esp8266')
	ARCH=xtensa
	PLATFORM=xtensa-lx106-elf
	CC = $(PLATFORM)-gcc
	CFLAGS = -fno-builtin -fno-inline-functions -nostdlib -mlongcalls -mtext-section-literals
	AS = $(PLATFORM)-as
	INC = -I/usr/local/xtensa-lx106-elf/lib/gcc/xtensa-lx106-elf/8.4.0/include/
	CFLAGS += -DLIBIO
	MACH=esp8266
endif

ifeq ($(TARGET), 'm68k')
	ARCH=m68k
	PLATFORM=$(ARCH)-linux-gnu
	CC = $(PLATFORM)-pcc
	CFLAGS = -fno-builtin
	CFLAGS = -mcpu=68000 -msoft-float -O
endif

ifeq ($(TARGET), 'linux')
	ARCH=x86_64
	PLATFORM=$(ARCH)-linux-gnu
	CC = amd64-linux-pcc
endif

ifeq ($(TARGET), 'pdp11')
	ARCH=pdp11
	PLATFORM=$(ARCH)-none
endif

CC ?= $(PLATFORM)-pcc
AS ?= $(PLATFORM)-as

MACH ?= $(ARCH)
INC ?= -I/usr/local/lib/pcc/$(PLATFORM)/1.2.0.DEVEL/include/

ASFLAGS =
CFLAGS += -Wall -O
INC += -nostdinc -I./include

SRCS = \
	src/ctype.c \
	src/getopt.c \
	src/printf.c \
	src/sscanf.c \
	src/stdio.c \
	src/stdlib.c \
	src/malloc.c \
	src/string.c \
	src/signal.c \
	src/time.c \
	src/unistd.c
HDRS = $(wildcard include/*.h include/sys/*.h include/machine/*.h)
OBJS = $(SRCS:.c=.o)


.PHONY: $(HDRS)

all:	libc.a libsys.a

install:	 install_headers install_libs

install_libs:	 libc.a libsys.a
	mkdir -p /usr/local/$(PLATFORM)/lib/
	cp libc.a libsys.a /usr/local/$(PLATFORM)/lib/

install_headers:
	mkdir -p /usr/local/$(PLATFORM)/include
	cp -r include/* /usr/local/$(PLATFORM)/include

libc.a:	$(OBJS)
	$(AR) crv $@ $^

LIBSYS_C_SOURCES = $(wildcard sys/$(MACH)_*.c)
LIBSYS_ASM_SOURCES = $(wildcard sys/$(MACH)_*.s)
LIBSYS_OBJECTS = $(LIBSYS_C_SOURCES:.c=.o) $(LIBSYS_ASM_SOURCES:.s=.o)
libsys.a: $(LIBSYS_OBJECTS)
	$(AR) crv $@ $^

clean:
	$(RM) -f $(OBJS) $(LIBSYS_OBJECTS) libc.a libsys.a

.SUFFIXES: .c .h .s .o

.c.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.s.o:
	$(AS) $(ASFLAGS) -c -o $@ $<
