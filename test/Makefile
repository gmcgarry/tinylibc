INC += -I../include
LDLIBS += ../libc.a ../libsys.a

ARCH=$(shell uname -s | tr [:upper:] [:lower:])
include $(ARCH)/Makefile.inc

CFLAGS += -g
LDFLASGS += -g

all:	simple hw time

simple:	simple.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

time:	time.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

hw:	hw.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean: 
	$(RM) *.o simple hw
